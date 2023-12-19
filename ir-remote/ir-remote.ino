int num = 0,numsav, num2 = 0,num2sav;


int ir_out = 16;
bool iraddress[] = {0, 0, 0, 0, 0, 0, 0, 0};
bool irdata   [] = {0, 1, 1, 1, 0, 0, 0, 1};

void ir_count(int i,int b) {
//   num=i;
//   num2=b;
   numsav =num;
   num2sav=num2;
   if (numsav>256)     {iraddress[0]=1;numsav=numsav-256;} else{iraddress[0]=0;}
   if (numsav>128)     {iraddress[1]=1;numsav=numsav-128;} else{iraddress[1]=0;}
   if (numsav>64 )     {iraddress[2]=1;numsav=numsav-64; } else{iraddress[2]=0;}
   if (numsav>32 )     {iraddress[3]=1;numsav=numsav-32; } else{iraddress[3]=0;}
   if (numsav>16 )     {iraddress[4]=1;numsav=numsav-16; } else{iraddress[4]=0;}
   if (numsav>8  )     {iraddress[5]=1;numsav=numsav-8;  } else{iraddress[5]=0;}
   if (numsav>4  )     {iraddress[6]=1;numsav=numsav-4;  } else{iraddress[6]=0;}
   if (numsav>2  )     {iraddress[7]=1;numsav=numsav-2;  } else{iraddress[7]=0;}
  
   if(num2sav>256)     {irdata [0]=1;num2sav=num2sav-256;} else{irdata   [0]=0;}
   if(num2sav>128)     {irdata [1]=1;num2sav=num2sav-128;} else{irdata   [1]=0;}
   if(num2sav>64 )     {irdata [2]=1;num2sav=num2sav-64; } else{irdata   [2]=0;}
   if(num2sav>32 )     {irdata [3]=1;num2sav=num2sav-32; } else{irdata   [3]=0;}
   if(num2sav>16 )     {irdata [4]=1;num2sav=num2sav-16; } else{irdata   [4]=0;}
   if(num2sav>8  )     {irdata [5]=1;num2sav=num2sav-8;  } else{irdata   [5]=0;}
   if(num2sav>4  )     {irdata [6]=1;num2sav=num2sav-4;  } else{irdata   [6]=0;}
   if(num2sav>2  )     {irdata [7]=1;num2sav=num2sav-2;  } else{irdata   [7]=0;}

   if(num>512){num=0;num2++;}

   num++;
}
void ir_write_high() {
  analogWrite(ir_out, 125);
  delayMicroseconds(560);
  analogWrite(ir_out, 0);
  delayMicroseconds(2250 - 560);
}
void ir_write_low () {
  analogWrite(ir_out, 125);
  delayMicroseconds(560);
  analogWrite(ir_out, 0);
  delayMicroseconds(560);
}
void ir_bracket   (int i) {
  analogWrite(ir_out, 125);
  delayMicroseconds(i);
  analogWrite(ir_out, 0);
}
void ir_wait     (int i) {
  delayMicroseconds(i);
}
void ir_address  () {
  for (int i = 0; i < 8; i++) {
    if (iraddress[i]) {
      ir_write_high();
    }
    else {
      ir_write_low();
    }
  }
  for (int i = 0; i < 8; i++) {
    if (iraddress[i]) {
      ir_write_low();
    }
    else {
      ir_write_high();
    }
  }
}
void ir_data     () {
  for (int i = 0; i < 8; i++) {
    if (irdata[i]) {
      ir_write_high();
    }
    else {
      ir_write_low();
    }
  }
  for (int i = 0; i < 8; i++) {
    if (irdata[i]) {
      ir_write_low();
    }
    else {
      ir_write_high();
    }
  }
}
void ir_serial_out(){
  for(int i=0;i<8;i++){Serial.print (iraddress[i]);}
  Serial.println();
  for(int i=0;i<8;i++){Serial.print (irdata[i]);}
  Serial.println();
  Serial.println("________");
  }
void ir_data_close_bits (){
    
    }
void ir_protocoll(int i,int b){
  ir_bracket(9000);
  ir_wait(4500);
  ir_address();
  ir_data();
  ir_wait(150000);
  ir_count(i,b);
  ir_serial_out();
  }
void viewsonic_projector(){
  ir_protocoll(0,113);
  ir_protocoll(0,50);
  ir_protocoll(128,64);
  ir_protocoll(16,16);
  ir_protocoll(16,48);
  for(int i=0;i<12;i++){
    ir_protocoll(16,16);}
  ir_protocoll(16,48);
  for(int i=0;i<10;i++){
    ir_protocoll(16,16);}
  ir_protocoll(16,48);
  for(int i=0;i<9;i++){
    ir_protocoll(16,16);}
  ir_protocoll(16,48);
  ir_protocoll(16,16);
  for(int i=0;i<5;i++){
    ir_protocoll(16,48);}
  for(int i=0;i<3;i++){
    ir_protocoll(16,16);}
  ir_protocoll(16,48);
  ir_protocoll(16,16);
  for(int i=0;i<4;i++){
    ir_protocoll(16,48);}
  ir_protocoll(16,16);
  ir_protocoll(16,48);
  ir_protocoll(16,151);
  ir_protocoll(16,160);
  }
void setup() {
  analogWriteFreq(38000);
  Serial.begin(115200);
}

void loop() {
  viewsonic_projector();
}
