#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int PC=0;
int label=1;
struct node{
    int PC;
    int label_num;
    struct node* next;
}first;

void R_type(int binary[32]);
void I_type1(int binary[32]);
void I_type2(int binary[32]);
void I_type3(int binary[32]);
void S_type(int binary[32]);
void J_type(int binary[32]);
void U_type(int binary[32]);
void B_type(int binary[32]);
long long HexToDecimal(char hexString[8]){
    long long decimalValue=0;
    for(int index=7;index>=0;index--){
        if(hexString[index]>='0'&& hexString[index]<='9'){
            decimalValue=decimalValue+(hexString[index]-48)*pow(16,7-index);
        }
        else if(hexString[index]>='A'&& hexString[index]<='F'){
            decimalValue=decimalValue+(hexString[index]-55)*pow(16,7-index);
        }
        else if(hexString[index]>='a'&& hexString[index]<='f'){
            decimalValue=decimalValue+(hexString[index]-87)*pow(16,7-index);
        }
    }
    return decimalValue;
}

void DecimalToBinary(long long decimal,int binary[32]){
    for(int index=0;index<32;index++){
        binary[index]=decimal%2;
        decimal=decimal/2;
    }
}
void DecimalToHex(long long decimal,char hexString[9]){
    int i=4;
    for(int index=0;index<8;index++){ 
        int remainder=decimal%16;
        if(remainder<=9){
            hexString[i]=(char)(remainder +48);
        }
        else{
           hexString[i]=(char)(remainder +87); 
        }       
        decimal=decimal/16;
        i--;
        while(i<0){
            break;
        }
    }
}
int extract_unsigned(int binary[32],int size,int end){
    int extractedpart=0;
    int position=end;
    int power=size-1;
    int index=0;
    while(index<size){
        extractedpart=extractedpart+binary[position]*pow(2,power);
        position--;
        index++;
        power--;
    }
    return extractedpart;
}
int extract_signed(int binary[32],int size,int end){
    if(binary[end]==0){
        return extract_unsigned(binary,size,end);
    }
    else if(binary[end]==1){
        return extract_unsigned(binary,size,end)-pow(2,size);
    }
    return 0;
}

void checkOpcode(int binary[32]){
    int opcode=extract_unsigned(binary,7,6);
    if(opcode==51){
        R_type(binary);
    }
    else if(opcode==19){
        I_type1(binary);
    }
    else if(opcode==3){
        I_type2(binary);
    }
    else if(opcode==103){
        I_type3(binary);
    }
    else if(opcode==99){
        B_type(binary);
    }
    else if(opcode==35){
        S_type(binary);
    }
    else if(opcode==111){
        J_type(binary);
    }
    else if(opcode==55||opcode==23){
        U_type(binary);
    }
    else{
        printf("Invalid Instruction\n");
    }
    return;
}

void R_type(int binary[32]){
    int funct7=extract_unsigned(binary,7,31);
    int rs2=extract_unsigned(binary,5,24);
    int rs1=extract_unsigned(binary,5,19);
    int funct3=extract_unsigned(binary,3,14);
    int rd=extract_unsigned(binary,5,11);
    if(funct3==0){
        if(funct7==0){
            printf("add ");
        }
        else if(funct7==32){
            printf("sub  ");
        }
        else{
            printf("Invalid Instruction\n");
            return;
        }
    }
    if(funct3==1){
        if(funct7!=0){
            printf("Invalid Instruction\n");
            return;
        }
        printf("sll  ");
    }
    if(funct3==2){
        if(funct7!=0){
            printf("Invalid Instruction\n");
            return;
        }
        printf("slt  ");
    }
    if(funct3==3){
        if(funct7!=0){
            printf("Invalid Instruction\n");
            return;
        }
        printf("sltu  ");
    }
    if(funct3==4){
        if(funct7!=0){
            printf("Invalid Instruction\n");
            return;
        }
        printf("xor  ");
    }
    if(funct3==5){
        if(funct7==0){
            printf("srl  ");
        }
        else if(funct7==32){
            printf("sra  ");
        }
        else{
            printf("Invalid Instruction\n");
            return;
        }
    }
    if(funct3==6){
        if(funct7!=0){
            printf("Invalid Instruction\n");
            return;
        }
        printf("or  ");
    }
    if(funct3==7){
        if(funct7!=0){
            printf("Invalid Instruction\n");
            return;
        }
        printf("and  ");
    }
    printf("x%d, x%d, x%d\n",rd,rs1,rs2);
}
void I_type1(int binary[32]){
    int imm=extract_signed(binary,12,31);
    int rs1=extract_unsigned(binary,5,19);
    int funct3=extract_unsigned(binary,3,14);
    int rd=extract_unsigned(binary,5,11);  
    if(funct3==0){
        printf("addi ");
    }
    else if(funct3==1){
        imm=extract_unsigned(binary,6,25);
        printf("slli ");
    } 
    else if(funct3==2){
        printf("slti ");
    } 
    else if(funct3==3){
        printf("sltiu ");
    } 
    else if(funct3==4){
        printf("xori ");
    } 
    else if(funct3==5){
        imm=extract_unsigned(binary,6,25);
        if(extract_unsigned(binary,6,31)==0){
            printf("srli ");
        }
        else{
            printf("srai ");
        }  
    } 
    else if(funct3==6){
        printf("ori ");
    }  
    else if(funct3==7){
        printf("andi ");
    }
    printf("x%d, x%d, %d\n",rd,rs1,imm);
}
void I_type2(int binary[32]){
    int imm=extract_signed(binary,12,31);
    int rs1=extract_unsigned(binary,5,19);
    int funct3=extract_unsigned(binary,3,14);
    int rd=extract_unsigned(binary,5,11);  
    if(funct3==0){
        printf("lb ");
    }
    else if(funct3==1){
        printf("lh ");
    }
    else if(funct3==2){
        printf("lw ");
    }
    else if(funct3==3){
        printf("ld ");
    }
    else if(funct3==4){
        printf("lbu ");
    }
    else if(funct3==5){
        printf("lhu ");
    }
    else if(funct3==6){
        printf("lwu ");
    }
    printf("x%d, %d(x%d)\n",rd,imm,rs1);
}
void S_type(int binary[32]){
    int rs2=extract_unsigned(binary,5,24);
    int rs1=extract_unsigned(binary,5,19);
    int funct3=extract_unsigned(binary,3,14);
    int immediate[12];
    int index=0;
    for(index=0;index<5;index++){
        immediate[index]=binary[index+7];
    }
    for(index=5;index<12;index++){
        immediate[index]=binary[20+index];
    }
    int imm=extract_signed(immediate,12,11);
    if(funct3==0){
        printf("sb ");
    }
    else if(funct3==1){
        printf("sh ");
    }
    else if(funct3==2){
        printf("sw ");
    }
    else if(funct3==3){
        printf("sd ");
    }
    printf("x%d, %d(x%d)\n",rs2,imm,rs1);
}
void I_type3(int binary[32]){
    int imm=extract_signed(binary,12,31);
    int rs1=extract_unsigned(binary,5,19);
    int funct3=extract_unsigned(binary,3,14);
    int rd=extract_unsigned(binary,5,11);
    struct node * current=&first;
    struct node * previous=NULL;
    int inserted=0;
    int print_label=0;
    while(current!=NULL){
        if(PC+imm>current->PC){
            previous=current;
            current=current->next;
        }
        else if(PC+imm<current->PC){
            struct node * newnode=malloc(sizeof(struct node));
            newnode->PC=PC+imm;
            newnode->label_num=label;
            newnode->next=current;
            previous->next=newnode;
            inserted=1;
            print_label=label;
            break;
        }
        else{
            inserted=1;
            print_label=current->label_num;
            break;
        }
    }
    if(inserted==0){
        struct node * newnode=malloc(sizeof(struct node));
        previous->next=newnode;
        newnode->PC=PC+imm;
        newnode->label_num=label;
        print_label=label;
    }
    if(funct3!=0){
        printf("Invalid Instruction\n");
        return;
    }
    printf("jalr x%d, x%d, L%d\n",rd,rs1,print_label);
    if(label==print_label){
        label++;
    }
}
void B_type(int binary[32]){
    int rs2=extract_unsigned(binary,5,24);
    int rs1=extract_unsigned(binary,5,19);
    int funct3=extract_unsigned(binary,3,14);
    int immediate[13];
    immediate[0]=0;
    int index;
    for(index=1;index<5;index++){
        immediate[index]=binary[7+index];
    }
    for(index=5;index<11;index++){
        immediate[index]=binary[20+index];
    }
    immediate[11]=binary[7];
    immediate[12]=binary[31];
    int imm=extract_signed(immediate,13,12);
    struct node * current=&first;
    struct node * previous=NULL;
    int inserted=0;
    int print_label=0;
    while(current!=NULL){
        if(PC+imm>current->PC){
            previous=current;
            current=current->next;
        }
        else if(PC+imm<current->PC){
            struct node * newnode=malloc(sizeof(struct node));
            //printf("node created\n");
            newnode->PC=PC+imm;
            newnode->label_num=label;
            newnode->next=current;
            previous->next=newnode;
            print_label=label;
            inserted=1;
            break;
        }
        else{
            inserted=1;
            print_label=current->label_num;
            break;
        }
    }
    if(inserted==0){
        struct node * newnode=malloc(sizeof(struct node));
        //printf("node created\n");
        previous->next=newnode;
        newnode->PC=PC+imm;
        newnode->label_num=label;
        print_label=label;
    }

    if(funct3==0){
        printf("beq ");
    }
    else if(funct3==1){
        printf("bne ");
    }
    else if(funct3==4){
        printf("blt ");
    }
    else if(funct3==5){
        printf("bge ");
    }
    else if(funct3==6){
        printf("bltu ");
    }
    else if(funct3==7){
        printf("bgeu ");
    }
    else{
        printf("Invalid Instruction\n");
        return;
    }
    printf("x%d, x%d, L%d\n",rs1,rs2,print_label);
    if(label==print_label){
        label++;
    }
}

void J_type(int binary[32]){
    int rd=extract_unsigned(binary,5,11);
    int immediate[21];
    immediate[0]=0;
    int index;
    for(index=1;index<11;index++){
        immediate[index]=binary[20+index];
    }
    immediate[11]=binary[20];
    for(index=12;index<20;index++){
        immediate[index]=binary[index];
    }
    immediate[20]=binary[31];
    int imm=extract_signed(immediate,21,20);
    struct node * current=&first;
    struct node * previous=NULL;
    int inserted=0;
    int print_label=0;
    while(current!=NULL){
        if(PC+imm>current->PC){
            previous=current;
            current=current->next;
        }
        else if(PC+imm<current->PC){
            struct node * newnode=malloc(sizeof(struct node));
            newnode->PC=PC+imm;
            newnode->label_num=label;
            newnode->next=current;
            previous->next=newnode;
            inserted=1;
            print_label=label;
            break;
        }
        else{
            inserted=1;
            print_label=current->label_num;
            break;
        }
    }
    if(inserted==0){
        struct node * newnode=malloc(sizeof(struct node));
        previous->next=newnode;
        newnode->PC=PC+imm;
        newnode->label_num=label;
        print_label=label;
    }
    printf("jal x%d, L%d\n",rd,print_label);
    if(label==print_label){
        label++;
    }
}
void U_type(int binary[32]){
    int imm=extract_unsigned(binary,20,31);
    int rd=extract_unsigned(binary,5,11);
    char hexString[9];
    DecimalToHex(imm,hexString);
    printf("lui x%d, 0x%s\n",rd,hexString);
}
void Decode(char hexString[8]){
    int binary[33]; 
    long long decimalValue=HexToDecimal(hexString);
    DecimalToBinary(decimalValue,binary);
    checkOpcode(binary);
}
int main(){
    printf("Give the name of file\n");
    char filename[256];
    scanf("%[^\n]s",filename);
    first.PC=0;
    first.label_num=0;
    first.next=NULL;
    char input[10];
    FILE * fileptr=fopen(filename,"r");
    if (fileptr == NULL) {
        perror("Error opening file");
    }
    else{
        char hexString[10];
        while (fscanf(fileptr, " %9s", hexString) == 1) {
            PC=PC+4;
            struct node * current=first.next;
            while(current!=NULL){
                if(PC==current->PC){
                    printf("L%d: ",current->label_num);
                    break;
                }
                else if(PC>current->PC){
                    current=current->next;
                }
                else{
                    break;
                }
            }
            Decode(hexString);            
        }
        fclose(fileptr);
    }
    struct node * current=first.next;
    struct node * previous=NULL;
    while(current!=NULL){
        previous=current;
        current=current->next;
        if(previous!=NULL){
            free(previous);
        }       
    }   
}
/*add x3, x4, x7 
beq x4, x7, L1
jal x0, L1
sd x5, 12(x6)
lui x9, 0x10000
L1: addi x9, x10, 12
lui x4 0xfffff
*/