#include <QDebug>
#include <QList>
/*************************************************
 * 问题描述： 一副从1到n的牌，每次从牌堆顶取一张放桌子上，
 *          再取一张放牌堆底，直到手上没牌，最后桌上的牌是从1到n有序，
 *          设计程序，输入n，输出牌堆的顺序数组。
 *
 * 示例：输入 n=5, 输出 (1, 5, 2, 4, 3)
 *
 * 原理解析： 假设手上有三张牌（a,b,c），模拟取牌过程后，桌子上牌的顺序是（a,c,b）,
 *          （a,c,b）与（1,2,3）一一对应，所以原来的顺序是（1,3,2）
**************************************************/
QList<int> func(int n){
    QList<int> cards;// 牌堆
    for(int i = 1; i <= n; i++){
        cards.push_back(i);// 数组【1-n】
    }

    QList<int> table;// 桌上的牌
    while (cards.size() != 0) {// 模拟取牌过程
        int top;
        // 从牌堆顶取一张牌放到桌子上
        top = cards[0];
        cards.pop_front();
        table.push_back(top);

        // 再取一张放牌堆底
        if(cards.size() != 0){
            top = cards[0];
            cards.pop_front();
            cards.push_back(top);
        }
    }
    QList<int> res;
    for(int i = 0; i < n; i++){
        res.push_back(0);// 初始化
    }
    for(int i = 0; i < n; i++){
        res[table[i]-1] = i+1;// 以值为索引赋值 ---画重点---
    }
    return res;
}

int main(int argc, char *argv[])
{
    qDebug()<<func(5);
}
