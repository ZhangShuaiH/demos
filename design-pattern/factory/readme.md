# 1. 工厂的创建方法
  可以创建一个具体产品（无形参），也可创建一个抽象产品的具体产品（有形参）
```c++
  Product *Factory::create(){// 无形参，只能创建一个固定的对象
      return new Product;
  }
  Product *Factory::create(string name){// 根据形参，创建不同具体对象
      if(name=="pro1"){
        return new Pro1;
      }else if(name=="pro2"){
        return new Pro2;
      }else{
        ...
      }
  }
```
# 2. 抽象
  具象是不同层次上的抽象
  
  苹果是红富士苹果、嘎啦苹果的抽象；红富士苹果是红富士甜苹果、红富士酸苹果的抽象；红富士甜苹果是红富士小甜苹果、红富士大甜苹果
  的抽象。抽象可无限向下分割。
  
  工厂可无限向下分割。
# 3. 封装
  可以将变化封装到类中、函数中、变量中。抽象的对象可以变化，变化就是抽象。
