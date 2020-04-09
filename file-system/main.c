#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define string char*
#define bool int
#define true 1
#define false 0
#define fnameSize 16    //文件名、路径名最大长度
#define unameSize 20    //用户名最大长度
#define userNumber 8    //用户的最大个数
#define pwSize 10       //密码最大长度
#define commandSize 16  //命令最大长度
#define commandNumber 5 //命令的最大个数
#define filesNumber 32  //文件夹下文件+文件夹的最大个数，文件最多占用的物理块数
#define allfilesNumber 1024 //所有文件+所有文件夹的最大数目
#define dirDepth 10     //目录的深度(级数)
#define hide 0          //权限：隐藏、不可删
#define read 1          //权限：可见、可读、不可删、默认权限
#define write 2         //权限：可见、可读、可写、不可删
#define bufferSize 1024 //创建文件，缓冲区大小

int commandPrompt[dirDepth];//命令提示符
char command[commandNumber][commandSize];//保存命令的字符串数组

typedef struct {//文件目录
    int id;//文件及文件夹总数最大9999
    char name[fnameSize];//文件、目录名
    bool isfile;
    char createTime[20];
    char updateTime[20];
    char author[unameSize];
    int right;
    int sizeOrNum;//文件大小或文件和文件夹数目
    int ids[filesNumber];//本目录下的文件及子目录id
}dir,*pdir;
dir dirs[allfilesNumber];

typedef struct { //用户名及密码
    int uid;
    char uname[unameSize];
    char password[pwSize];
}user,*puser;
user users[userNumber];

#endif // HEAD_H_INCLUDED


char *getCurTime(){
    time_t t;
    struct tm *lt;
    t = time(NULL);
    lt = localtime(&t);
    char nowtime[24];
    memset(nowtime, 0, sizeof(nowtime));
    strftime(nowtime, 24, "%Y.%m.%d %H:%M:%S", lt);
    return nowtime;
}


int getUid(){
    int i;
    int uid;//上级目录的id
    for(i=dirDepth-1; commandPrompt[i] == -1 && i>0; i--);//找到上级目录id
    if(i == -1){
        printf("错误！");
        return -1;
    }
    if(i == 0)
        uid = 0;
    else
        uid = commandPrompt[i];
    return uid;
}


void init(){//初始化目录信息、命令提示符
    int i,j;
    for(i=0; i<allfilesNumber; i++){//初始化目录信息，id=-1,ids[i]=-1
        dirs[i].id = -1;
        strcpy(dirs[i].createTime, "null");
        strcpy(dirs[i].updateTime, "null");
        dirs[i].right = -1;
        for(j=0; j<filesNumber; j++){
            dirs[i].ids[j] = -1;
        }
    }

    for(i=0; i<dirDepth; i++){//初始化命令提示符
        commandPrompt[i] = -1;
    }
    loadDirs();//加载目录信息到内存，保存到结构体数组dir dirs[allfilesNumber]中
    loadUsers();//加载用户信息到user users[userNumber][unameSize];
}


bool loadDirs(){//加载目录信息到内存，保存到结构体数组dirs[allfilesNumber]中
    int i=0;
    int j=0;
    FILE *fp;
    char c;
    fp = fopen("1", "r");
    for(i=0; !feof(fp) && i<allfilesNumber; i++){
        fread(&dirs[i], sizeof(dir), 1, fp);//加载id，name，isfile等信息
//        fscanf(fp, "%d,%s,%d,", &dirs[i].id, dirs[i].name, &dirs[i].isfile);//加载id，name，isfile信息
//        for(j=0; (c=fgetc(fp)) != '\n' && j<filesNumber; j++){//加载ids[]信息
//            ungetc(c, fp);
//            fscanf(fp, "%d,", &dirs[i].ids[j]);
//        }
    }
    fclose(fp);
    return true;
}


bool loadUsers(){//加载用户信息到user users[userNumber][unameSize];
    int i;
    for(i=0; i<userNumber; i++){//初始化users[]
        users[i].uid = -1;
    }

    FILE *fp;
    fp = fopen("0", "r");
    for(i=0; !feof(fp) && i<userNumber; i++){//加载用户信息
        //fscanf(fp, "%d,%s,%s\n", &users[i].uid, users[i].uname, users[i].password);
        fread(&users[i], sizeof(user), 1, fp);
    }
    fclose(fp);
    return true;
}


bool login(){//用户登录，参数：用户名、密码
    int i;
    for(i=0; strcmp(users[i].uname, command[1]) != 0 && i<userNumber; i++);
    if(i == userNumber){//判断用户名是否正确
        printf("用户名错误!");
        return false;
    }
    else{
        if(strcmp(users[i].password, command[2]) != 0){//判断密码是否正确
            printf("密码错误!");
            return false;
        }
        else{
            commandPrompt[0] = i;//将用户名保存到命令提示符中
            return true;
        }
    }
}

bool makeDir(){//创建文件夹
    int i,k;
    int fn;//上级目录的文件或文件夹数目
    int uid;//上级目录的id
    uid = getUid();

    fn = dirs[uid].sizeOrNum;
    for(k=0; k<fn; k++){
        if(strcmp(dirs[dirs[uid].ids[k]].name, command[1]) == 0){//判断重名文件或文件夹
            printf("文件夹名冲突!");
            return false;
        }
    }

    for(i=0; dirs[i].id!=-1 && i<allfilesNumber; i++);//为新文件夹分配id
    if(i == allfilesNumber){
        printf("无法创建文件夹！");
        return false;
    }

    if(strcmp("h", command[2]) == 0){//判断权限是否正确
        dirs[i].right = hide;
    }
    else if(strcmp("r", command[2]) == 0 || strcmp("", command[2]) == 0){
        dirs[i].right = read;
    }
    else if(strcmp("w", command[2]) == 0){
        dirs[i].right = write;
    }
    else{
        printf("权限错误!");
        return false;
    }

    dirs[i].id = i;//填写新文件夹信息
    strcpy(dirs[i].name, command[1]);
    dirs[i].isfile = false;
    strcpy(dirs[i].author, users[commandPrompt[0]].uname);
    strcpy(dirs[i].createTime, getCurTime());
    dirs[i].sizeOrNum = 0;

    int tid;//新文件夹id
    tid = i;

    for(i=dirDepth-1; commandPrompt[i] == -1 && i>0; i--);//找上级目录
    if(i == -1){
        printf("错误！");
        return false;
    }
    commandPrompt[i+1] = tid;//改变系统状态，添加当前目录到commandPrompt[]

    dirs[uid].ids[dirs[uid].sizeOrNum] = tid;//更新上级目录的文件夹id
    dirs[uid].sizeOrNum++;//更新上级目录的文件夹数目
    return true;
}


void printCommandPrompt(){
    int i;
    if(commandPrompt[0] == -1)
        printf("\nFMS$");
    else{
        printf("\n%s ", users[commandPrompt[0]].uname);
        for(i=1; commandPrompt[i] != -1; i++){
            printf("%s/", dirs[commandPrompt[i]].name);
        }
        printf("$");
    }
}


bool printConfirm(char *pInf){
    char str[5];
    while(true){
        printf("确认%s? y/n:", pInf);
        scanf("%s", str);
        if(strcmp("y", str) == 0){
            return true;
        }
        else if(strcmp("n", str) == 0){
            return false;
        }
        else{
            printf("命令错误!");
        }
    }
}

void readcommand(){//读取命令，拆分为单词
    char c;
    int i,j;
    for(i=0; i<commandNumber; i++){//清空命令
        strcpy(command[i], "");
    }

    fflush(stdin);//清空标准输入流
    for(i=0, j=0; (c=getchar())!='\n' && j<commandNumber && i<commandSize; i++){//读取命令，标准输入
        if(c == ' '){
            command[j][i] = '\0';
            j++;
            i = -1;
        }
        else{
            command[j][i] = c;
        }
    }
    command[j][i] = '\0';
}


//读一行文件，返回二维字符数组
char *readline(FILE *fp){
    char line[1024];
    char res[1024];
    int i;
    if (!feof(fp)){
        fgets(line, 1024, fp);
        for(i=0; line[i] != '\n'; i++){
            res[i]=line[i];
        }
        res[i] = '\0';
        return res;
    }
    else{
        return NULL;
    }
}


bool saveDirs(){//保存目录信息到物理块1
    int length;
    int i;
    int j;
    for(length=allfilesNumber-1; dirs[length].id==-1 && length>0; length--);//倒序找到第一个id!=-1的dirs[]
    FILE *fp;
    fp = fopen("1", "w");
    for(i=0; i<=length; i++){
        fwrite(&dirs[i], sizeof(dir), 1, fp);//保存id，name，isfile信息
    }
    fclose(fp);
    return true;
}


//dir
bool showDirs(){//显示当前路径下的文件和文件夹
    //获取上级目录id
    int uid = getUid();
    //获取子文件夹id1、id2...
    //获取子文件id1、id2...
    int i, j, k;
    int sid;//暂存子目录id
    int dids[filesNumber];//暂存子文件夹id
    int fids[filesNumber];//暂存子文件id
    for(i=0; i<filesNumber; i++){//初始化
        dids[i] = -1;
        fids[i] = -1;
    }
    for(i=0,j=0,k=0; (sid=dirs[uid].ids[i])!=-1 && i<filesNumber; i++){
        if(!dirs[sid].isfile && (dirs[sid].right!=hide || strcmp(dirs[sid].author, users[commandPrompt[0]].uname)==0 ) )
            dids[j++] = sid;
        else if(dirs[sid].isfile && (dirs[sid].right!=hide || strcmp(dirs[sid].author, users[commandPrompt[0]].uname)==0 ))
            fids[k++] = sid;
    }

    //显示子目录名
    printf("文件夹:\t%d\n", j);//显示文件夹名
    for(i=0; (sid=dids[i])!=-1 && i<filesNumber; i++){
        printf("\t%s\n", dirs[sid].name);
    }

    printf("文件:\t%d\n", k);//显示文件名
    for(i=0; (sid=fids[i])!=-1 && i<filesNumber; i++){
        printf("\t%s\n", dirs[sid].name);
    }
    return true;
}


bool signin(){//用户注册，参数：用户名、密码、确认密码
    int i;
    for(i=0; strcmp(users[i].uname, command[1]) != 0 && i<userNumber; i++);
    if(i < userNumber){//判断用户名是否重复
        printf("用户名已存在!");
        return false;
    }
    if(strcmp("", command[3]) == 0){
        printf("未输入确认密码！");
        return false;
    }
    if(strcmp(command[2], command[3]) != 0){//密码不一致，注册失败
        printf("注册失败，密码不一致!");
        return false;
    }

    for(i=0; users[i].uid != -1 && i<userNumber; i++);//找到第一个id != -1的users[]
    users[i].uid = i;
    strcpy(users[i].uname, command[1]);
    strcpy(users[i].password, command[2]);

    FILE *fp;
    fp = fopen("0", "a");
    fwrite(&users[i], sizeof(user), 1, fp);//保存用户信息
    fclose(fp);
    loadUsers();
    return true;
}


//申请一个空闲物理块
char *applyBlock(){
    int i = 0;
    char *depth;//栈深
    int idepth;
    FILE *fp;
    fp = fopen("33","r");
    depth = readline(fp);
    idepth = atoi(depth);
    char stack1[idepth+1][5];

    //读物理块33中的内容到栈
    strcpy(stack1[0], depth);
    for(i=1; i<idepth+1; i++){
        strcpy(stack1[i], readline(fp));
    }
    fclose(fp);

    char top[5];//返回栈顶原素
    strcpy(top, stack1[idepth]);

    idepth--;//栈深减一
    itoa(idepth, stack1[0], 10);

    fp = fopen("33", "w");
    if(idepth == 0){
        FILE *fpo;
        fpo = fopen(top, "r");
        char c;
        while((c = fgetc(fpo)) != EOF)//复制栈顶物理块内容到物理块33
            fputc(c, fp);
        fclose(fpo);
    }
    else if(idepth != 0){//将修改后的栈中的内容写到物理块33
        for(i=0; i<idepth+1; i++){
            fputs(stack1[i], fp);
            fputc('\n', fp);
        }
    }
    fclose(fp);
    return top;
}

//cd dirname
bool changeDir(){//改变路径
    int i;
    if(strcmp("..", command[1]) == 0){//返回上级目录
        for(i=1; commandPrompt[i] != -1 && i<dirDepth; i++);
        if(i == 1){
            return true;
        }
        commandPrompt[i-1] = -1;//更新命令提示符
        return true;
    }

    int uid;//上级目录的id
    uid = getUid();

    int k;
    int fn;//上级目录的文件夹和文件数目
    fn = dirs[uid].sizeOrNum;
    for(k=0; strcmp(dirs[dirs[uid].ids[k]].name, command[1]) != 0 && k<fn; k++);//找到子目录id
    int sid = dirs[dirs[uid].ids[k]].id;

    if(k == fn || dirs[sid].isfile){
        printf("文件夹不存在!");
        return false;
    }
    else{
        for(i=1; commandPrompt[i] != -1 && i<dirDepth; i++);
        if(i == dirDepth){
            printf("已达最大级数!");
            return false;
        }
        if(dirs[sid].right==hide && strcmp(dirs[sid].author, users[commandPrompt[0]].uname)!=0 ){
            printf("文件夹不可见!");
            return false;
        }
        commandPrompt[i] = sid;//更新命令提示符
    }

    return true;
}


bool format(){//格式化空闲块，清空所有物理块33~344；清空目录信息
    if(printConfirm("格式化") == false){
        return false;
    }

    int i,j;
    char bname[5];
    FILE *fp;
    fp = fopen("33", "w");
    fprintf(fp, "12\n");
    for(i = 34; i < 46; i++)
        fprintf(fp, "%d\n", i);
    fclose(fp);

    fp = fopen("34", "w");
    fprintf(fp, "50\n");
    for(i = 46; i < 96; i++)
        fprintf(fp, "%d\n", i);
    fclose(fp);

    int block[8] = {46,96,146,196,246,296,346,396};
    for(j=0; j<8; j++){
        itoa(block[j], bname, 10);
        fp = fopen(bname, "w");
        fprintf(fp, "50\n");
        for(i = block[j]+50; i < block[j]+100; i++)
            fprintf(fp, "%d\n", i);
        fclose(fp);
    }

    fp = fopen("446", "w");
    fprintf(fp, "49\n");
    fprintf(fp, "0\n");
    for(i = 496; i < 545; i++)
        fprintf(fp, "%d\n", i);
    fclose(fp);

    fp = fopen("1", "w");//清空目录信息
    fclose(fp);

    //int i,j;
    for(i=0; i<allfilesNumber; i++){//清空目录信息，id=-1,ids[i]=-1
        dirs[i].id = -1;
        strcpy(dirs[i].createTime, "null");
        strcpy(dirs[i].updateTime, "null");
        for(j=0; j<filesNumber; j++){
            dirs[i].ids[j] = -1;
        }
    }
    //初始化根目录信息
    dirs[0].id = 0;
    strcpy(dirs[0].name, "root");
    dirs[0].isfile = false;
    strcpy(dirs[0].createTime, getCurTime());
    dirs[0].sizeOrNum = 0;
    saveDirs();
    return true;
}


//删除文件后，释放一个物理块
bool freeBlock(char *id){
    int i = 0;
    char depth[5];//栈深
    int idepth;
    FILE *fp;
    fp = fopen("33","r");
    strcpy(depth, readline(fp));
    idepth = atoi(depth);
    char stack[idepth+1][5];

    //读物理块33中的内容到栈
    strcpy(stack[0], depth);
    for(i=1; i<idepth+1; i++){
        strcpy(stack[i], readline(fp));
    }
    fclose(fp);

    FILE *fpi;
    fpi = fopen("33", "w");
    if(idepth == 50){
        FILE *fpo;
        fpo = fopen(id, "w");
        for(i=0; i<idepth+1; i++){//将栈中元素写入物理块id
            fputs(stack[i], fpo);
            fputc('\n', fpo);
        }
        fclose(fpo);

        fputs("1", fpi);
        fputc('\n', fpi);
        fputs(id, fpi);
        fputc('\n', fpi);
    }
    else{//栈深加一，将id写入栈顶，并将栈写入物理块33
        idepth++;
        itoa(idepth, stack[0], 10);
        strcpy(stack[idepth], id);
        for(i=0; i<idepth+1; i++){
            fputs(stack[i], fpi);
            fputc('\n', fpi);
        }
    }
    fclose(fpi);
}


//查找名为name的子目录id
int getIdByName(int uid, int nameId){
    int sid;
    int i;
    for(i=0; (sid=dirs[uid].ids[i])!=-1 && i<filesNumber; i++){
        if(strcmp(dirs[sid].name, command[nameId]) == 0){
            break;
        }
    }
    if(sid == filesNumber || sid == -1){
        return -1;
    }
    return sid;
}

//show filename/dirname
bool showDirInfo(){//显示子文件夹或子文件的基本信息
    //获取上级目录id
    int uid = getUid();
    //查找名为name的子目录id
    int sid = getIdByName(uid, 1);
    if(sid == -1){
        printf("无此目录!");
        return false;
    }

    //显示子目录基本信息
    int isfile = dirs[sid].isfile;
    int right = dirs[sid].right;
    int sizeOrNum = dirs[sid].sizeOrNum;
    if(right!=hide || strcmp(dirs[sid].author, users[commandPrompt[0]].uname)==0 ){
        if(isfile == true){
            printf("类型\t\t文件\n");
        }
        else{
            printf("类型\t\t文件夹\n");
        }

        if(right == hide){
            printf("权限\t\t隐藏\n");
        }
        else if(right == read){
            printf("权限\t\t可读\n");
        }
        else{
            printf("权限\t\t可写\n");
        }

        printf("文件名\t\t%s\n", dirs[sid].name);
        printf("创建者\t\t%s\n", dirs[sid].author);
        printf("创建时间\t%s\n", dirs[sid].createTime);
        if(isfile == true){
            printf("更新时间\t%s\n", dirs[sid].updateTime);
            printf("文件大小\t%d字节\n", dirs[sid].sizeOrNum);
        }
        else{
            printf("子目录数\t%d\n", dirs[sid].sizeOrNum);
        }
    }
    else{
        printf("文件已隐藏，无权限查看!");
        return false;
    }
    return true;
}

//rename srcname desname
bool renameDir(){//改变目录名
    //获取上级目录id
    int uid = getUid();
    //获取名为srcname的子目录id
    int srcid = getIdByName(uid, 1);
    if(srcid == -1){
        printf("无此目录!");
        return false;
    }
    if(strcmp(dirs[srcid].author, users[commandPrompt[0]].uname)!=0){
        printf("无重命名权限!");
        return false;
    }
    //获取名为desname的子目录id 判重
    int desid = getIdByName(uid, 2);
    if(desid != -1){
        printf("目录已存在!");
        return false;
    }

    //确认重命名
    printConfirm("重命名");

    //更新子目录的目录信息
    strcpy(dirs[srcid].name, command[2]);
    return true;
}

//write filename
bool writeFile(){//写文件
    //获取上级目录id
    int uid = getUid();
    //查找名为name的文件id
    int sid = getIdByName(uid, 1);
    if(sid == -1 || !dirs[sid].isfile){
        printf("文件名错误!");
        return false;
    }
    if(dirs[sid].right!=write && strcmp(dirs[sid].author, users[commandPrompt[0]].uname)!=0 ){
        printf("无写文件权限!");
        return false;
    }

    //读标准输入流到buffer[]
    printf("输入(以'#'结束)：\n");
    char c;
    char buffer[bufferSize];
    int len;//文件长度
    int i;
    for(i=0; ( buffer[i]=getchar() )!='#' && i<bufferSize-1; i++);//读文件到缓冲区
    buffer[i] = '\0';
    len = i+1;

    if( !printConfirm("保存文件") ){
        return false;
    }

    int blockn;//分配物理块个数
    char bkid[5];//物理块id
    blockn = len%512 == 0? len/512:len/512+1;
    FILE *fp;
    int j;
    for(i=0; i<blockn; i++){
        strcpy(bkid, applyBlock());//申请空闲物理块
        fp = fopen(bkid, "w");
        for(j=0; (c=buffer[i*512+j])!='\0' && j<512; j++ ){
            fputc(c, fp);
        }
        fclose(fp);
        //更新物理块id
        dirs[sid].ids[i] = atoi(bkid);
    }

    //更改文件的目录信息size、updateTime
    dirs[sid].sizeOrNum = len;
    strcpy(dirs[sid].updateTime, getCurTime());
    return true;
}

//read filename
bool readFile(){//读文件
    //获取上级目录id
    int uid = getUid();
    //查找名为name的子目录id
    int fid = getIdByName(uid, 1);
    if(fid == -1 || !dirs[fid].isfile){
        printf("文件名错误!");
        return false;
    }
    if(dirs[fid].right==hide && strcmp(dirs[fid].author, users[commandPrompt[0]].uname)!=0 ){
        printf("无读文件权限!");
        return false;
    }

    int i;
    if(dirs[fid].ids[0] == -1){
        printf("文件为空!");
        return true;
    }
    int bkid;//物理块id
    char fname[5];
    FILE *fp;
    char c;
    int j;
    for(i=0; (bkid=dirs[fid].ids[i])!= -1 && i<filesNumber; i++){
        itoa(bkid, fname, 10);
        fp = fopen(fname, "r");
        for(j=0; (c=fgetc(fp)) != EOF; j++ ){
            printf("%c", c);
        }
        fclose(fp);
    }
    return true;
}

//create filename right
bool createFile(){//创建文件
    int k;
    int uid;//上级目录id
    int fid;//新文件id
    uid = getUid();

    int fn;//上级目录的文件或文件夹数目
    fn = dirs[uid].sizeOrNum;
    for(k=0; k<fn; k++){
        if(strcmp(dirs[dirs[uid].ids[k]].name, command[1]) == 0){//判断重名文件或文件夹
            printf("文件名冲突!");
            return false;
        }
    }
    int right;//文件权限
    if(strcmp("h", command[2]) == 0){//判断权限是否正确
        right = hide;
    }
    else if(strcmp("r", command[2]) == 0 || strcmp("", command[2]) == 0){
        right = read;
    }
    else if(strcmp("w", command[2]) == 0){
        right = write;
    }
    else{
        printf("权限错误!");
        return false;
    }

    //为新文件分配id
    int i;
    for(i=0; dirs[i].id!=-1 && i<allfilesNumber; i++);
    if(i == allfilesNumber){
        printf("无法创建文件夹！");
        return false;
    }
    fid = i;

    //填写新文件信息
    strcpy(dirs[fid].author, users[commandPrompt[0]].uname);
    strcpy(dirs[fid].createTime, getCurTime());
    dirs[fid].id = fid;
    dirs[fid].isfile = true;
    strcpy(dirs[fid].name, command[1]);
    dirs[fid].right = right;
    dirs[fid].sizeOrNum = 0;

    //更新上级目录信息
    dirs[uid].ids[dirs[uid].sizeOrNum] = fid;//更新上级目录的文件夹id
    dirs[uid].sizeOrNum++;//更新上级目录的文件夹数目

    return true;
}

//del filename/dirname
bool delDir(){//删除当前路径下的文件或文件夹
    //询问确认删除？
    if(!printConfirm("删除")){
        return false;
    }
    //获取上级目录id
    int uid = getUid();
    //查找名为name的子目录id
    int sid = getIdByName(uid, 1);
    //删除子目录下的所有文件
    int ids[allfilesNumber];//待删除目录id
    int sids[filesNumber];//子目录id
    sids[0] = sid;
    int i, j, k;
    int tid;//临时id
    char strid[5];
    for(i=0, j=1; i<j; i++){
        tid = sids[i];
        bool isfi = true;//是文件
        if( dirs[tid].isfile ){
            for(k=0; dirs[tid].ids[k] != -1 && k<filesNumber; k++){
                itoa(dirs[tid].ids[k], strid, 10);
                freeBlock(strid);
                printf("释放物理块\t%d\n", dirs[tid].ids[k]);
            }
        }

        else{
            isfi = false;
            for(k=0; dirs[tid].ids[k] != -1 && k<dirs[tid].sizeOrNum; k++){
                sids[j++] = dirs[tid].ids[k];
            }
        }

        //删除子目录下的所有目录信息
        //itoa(tid, strid, 10);
        //freeBlock(strid);
        if(isfi){
            printf("删除文件\t%s\n", dirs[tid].name);
        }
        else{
            dirs[tid].id = -1;
            printf("删除文件夹\t%s\n", dirs[tid].name);
        }
    }
    //更新上级目录信息，ids、sizeOrNum
    for(k=0; dirs[uid].ids[k] != -1 && k<filesNumber; k++){
        if(dirs[uid].ids[k] == sid){
           dirs[uid].ids[k]  = dirs[uid].ids[dirs[uid].sizeOrNum-1];
           dirs[uid].ids[dirs[uid].sizeOrNum] = -1;
           dirs[uid].sizeOrNum--;
        }

    }

    return true;
}

//cr filename/dirname right
bool changeRight(){//改变目录权限
    //获取上级目录id
    int uid = getUid();
    //获取名为srcname的子目录id
    int sid = getIdByName(uid, 1);
    if(sid == -1){
        printf("无此目录!");
        return false;
    }
    //判断能否修改权限
    if(strcmp(dirs[sid].author, users[commandPrompt[0]].uname)!=0){
        printf("无法修改权限!");
        return false;
    }

    //更新权限
    if(strcmp("h", command[2]) == 0){//判断权限是否正确
        dirs[sid].right = hide;
    }
    else if(strcmp("r", command[2]) == 0 || strcmp("", command[2]) == 0){
        dirs[sid].right = read;
    }
    else if(strcmp("w", command[2]) == 0){
        dirs[sid].right = write;
    }
    else{
        printf("权限错误!");
        return false;
    }

    return true;
}

void help(){
    printf("命令输入错误main！\n");
    printf("signin username password confimpassword  ..................注册\n");
    printf("login username password                  ..................登录\n");
    printf("quit                                     ..................退出系统\n");
    printf("format                                   ..................格式化\n");
    printf("mkdir dirname [right]                    ..................创建目录\n");
    printf("cd dirname                               ..................改变目录\n");
    printf("dir                                      ..................显示目录列表\n");
    printf("show dirname/filename                    ..................显示目录信息\n");
    printf("create filename [right]                  ..................创建文件\n");
    printf("write filename                           ..................写文件\n");
    printf("read filename                            ..................读文件\n");
    printf("rename srcdirname desdirname             ..................重命名目录\n");
    printf("cd..                                     ..................返回上一级\n");
    printf("cr dirname newright                      ..................改变权限\n");
    printf("del dirname                              ..................删除目录\n");
    printf("logout                                   ..................退出登录\n");
}

int main()
{
    init();//初始化目录信息、命令提示符
//    loadDirs();//加载目录信息到内存，保存到结构体数组dir dirs[allfilesNumber]中
//    loadUsers();//加载用户信息到user users[userNumber][unameSize];
    lab:
    while(commandPrompt[0] == -1){//登录、注册、退出
        printCommandPrompt();
        readcommand();
        if(strcmp(command[0], "signin")==0)
            signin();//注册
        else if(strcmp(command[0], "")==0);
        else if(strcmp(command[0], "login")==0)
            login();//登录
        else if(strcmp(command[0], "quit")==0)
            return 0;
        else
            help();
    }

    while(true){//登录后可以输入的命令
        printCommandPrompt();
        readcommand();
        //printf("%s\n", command[0]);
        if(strcmp(command[0], "format")==0)
            format();//格式化
        else if(strcmp(command[0], "")==0);
        else if(strcmp(command[0], "mkdir")==0)
            makeDir();//创建新目录
        else if(strcmp(command[0], "cd")==0)
            changeDir();//改变当前目录
        else if(strcmp(command[0], "dir")==0)
            showDirs();
        else if(strcmp(command[0], "show")==0)
            showDirInfo();
        else if(strcmp(command[0], "create")==0)
            createFile();
        else if(strcmp(command[0], "write")==0)
            writeFile();
        else if(strcmp(command[0], "read")==0)
            readFile();
        else if(strcmp(command[0], "rename")==0)
            renameDir();
        else if(strcmp(command[0], "cd..")==0){
            int i;
            for(i=1; commandPrompt[i] != -1 && i<dirDepth; i++);
            if(i == 1){
            continue;
            }
            commandPrompt[i-1] = -1;//更新命令提示符
        }
        else if(strcmp(command[0], "cr")==0)
            changeRight();
        else if(strcmp(command[0], "del")==0)
            delDir();
        else if(strcmp(command[0], "logout")==0){
            int ii;
            for(ii=0; ii<dirDepth; ii++){
                commandPrompt[ii] = -1;
            }
            goto lab;
        }
        else if(strcmp(command[0], "quit")==0){
            saveDirs();
            return 0;
        }
        else
            help();
    }
}
