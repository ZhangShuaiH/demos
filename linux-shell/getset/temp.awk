{
printf(" \
/**\n \
 *@brief 获取 %s \n \
 *@return %s %s\n \
**/\n \
const %s &Get%s(){return this->m_%s;}\n\n",

$3, 
$1, $2, 
$1, $2, $2);

printf(" \
/**\n \
 *@brief 设置 %s\n \
 *@param[in] %s %s\n \
**/\n \
void Set%s(const %s &%s){this->m_%s = %s;}\n\n",

$3, 
tolower(substr($2,1,1))substr($2,2), $3, 
$2, $1, tolower(substr($2,1,1))substr($2,2), $2, tolower(substr($2,1,1))substr($2,2));
}
