string strAdd(const string &num1, const string &num2){
    int n1 = num1.size();
    int n2 = num2.size();
    if(n1==0 || n2==0)
        return "";
    int n3 = n1>n2 ? n1+1:n2+1;
    string res(n3, '0');
    int i=0;
    int sum=0;
    int carry=0;
    for(; i<n1 && i<n2; i++){
        if(isdigit(num1[n1-1-i]) && isdigit(num2[n2-1-i])){
            sum = carry + (num1[n1-1-i]-'0') + (num2[n2-1-i]-'0');
            carry = sum/10;
            res[n3-1-i] = sum%10 + '0';
        }else {
            return "";
        }
    }

    for(; i<n1; i++){
        if(isdigit(num1[n1-1-i])){
            sum = carry + (num1[n1-1-i]-'0');
            carry = sum/10;
            res[n3-1-i] = sum%10 + '0';
        }else {
            return "";
        }
    }

    for(; i<n2; i++){
        if(isdigit(num2[n2-1-i])){
            sum = carry + (num2[n2-1-i]-'0');
            carry = sum/10;
            res[n3-1-i] = sum%10 + '0';
        }else {
            return "";
        }
    }
    if(carry == 1){
        res[n3-1-i] = '1';
        return res;
    }else {
        return res.substr(1, n3-1);
    }
}
