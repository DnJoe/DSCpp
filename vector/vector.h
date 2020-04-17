//版权....
//许可证....
//Code by JoeD. GKJoeD@gmail.com
//清华大学邓俊辉数据结构公开课编程练习代码，参考google C++ style编写
//此程序为接口编写 按照邓公给的接口填写，必要时改变一定的命名方式


typedef int Rank; //整数秩，提高代码可读性；首字母大写是为了更有区分度
#define INIT_CAPACITY 10 //初始化容量

template <typename T> class Vector {
//每一个界定符内，声明顺序为 1.typedefs和enums；2. 常量；3.构造函数；
//4.析构函数；5.成员函数（含静态数据成员）；6.成员变量（含静态成员变量）
 public:
  //构造函数
  Vector(int c = INIT_CAPACITY, int s = 0, T v = 0) //直接构造，容量c、规模s、元素初始值v
  { elem_ = new T[capacity_ = c]; for (size_ = 0; size_ < s; elem_[size_++] = v) ; }
  //以下可以统一调用内部方法copyFrom(T *Arr, int lo, int hi)
  Vector(T const *Arr, Rank n) { copyFrom(*Arr, 0, n); }  //数据整体复制
  Vector(T const *Arr, Rank lo, Rank hi) { copyFrom(*Arr, lo, hi); }  //数组区间复制
  Vector(Vector<T> const& V) { copyFrom(V.elem_, 0, V.size_); } //向量整体复制
  Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V.elem_, lo, hi); } //向量区间复制

  //析构函数
  ~Vector() { delete [] elem_; }

  //成员函数
  Rank size() { return size_; } //获取当前数组容量
  bool empty() { return 0 == size_ ? true : false; }  //判空操作  ！看邓公为什么可以那么写
  //成员函数-操作符重载 ※※不会
  T& operator[] (Rank r); //循秩访问
  const T& operator[] (Rank r) const; //仅限于做右值的版本？？？？
  Vector<T> & operator= (Vector<T> const&); //重载复制运算符，以便直接克隆 ||为何不重载"<"和"<"???
  //成员函数-插入删除
  Rank insert(Rank r, T const& e);  //插入元素，返回当前位置
  Rank insert(T const& e) { return insert(size_, e); } //默认插入末端
  int remove(Rank lo, Rank hi); //删除区间元素，返回三处个数
  T remove(Rank r); //删除指定秩的元素并返回其值，比一步删除表示多步删除高效
                    //但是由于要返回，所以不能直接写
  //成员函数-查找操作 ||整体查找使特殊的区间查找
  Rank find(T const& e) { return find(e, 0, size_); } //无序序列整体查找
  Rank find(T const& e, Rank lo, Rank hi) const;  //无序向量区间查找
  Rank search(T const& e) { return search(e, 0, size_); } //有序向量整体查找  ！与邓公有别
  Rank search(T const& e, Rank lo, Rank hi) const;  //有序向量区间查找
  //成员函数-排序操作；；几种排序算法的随机搭配，测试用，
    //一般可以根据特定情况选取特定方法，把private中的几个拿出来即可
  void sort(Rank lo, Rank hi);  //[lo, hi)局部排序
  void sort() { sort(0, size_); } //整体排序
  void unsort(Rank lo, Rank hi);  //[lo, hi)局部置乱，测试sort用
  void unsort() { unsort(0, size_); } //整体置乱
  int duplicate();  //无需向量去重，返回去除的个数
  int uniquify(); //有序向量去重
  //成员函数-遍历及其封装
  void traverse(void(* ) (T&));
  template <typename VST> void teaverse(VST&);
 

 protected: 
  //成员函数
  void expand();  //扩容
  void shrink();  //规模缩减
  void copyFrom(T const *Arr, Rank lo, Rank hi);  //通过复制构造向量
  //成员函数-几种查找算法 ||可以和邓公一样组织？连什么include都没有？可以，sort中include就行※pragma once的作用？
  //Rank binSearch //二分查找
   //斐波那契查找
   //插值查找
  //成员函数-几种排序算法
  Rank max(Rank lo, Rank hi); //选取最大元素
  bool bubble(Rank lo, Rank hi);  //冒泡排序算法
  void bubblesort(Rank lo ,Rank hi);  //冒泡排序
  void merge(Rank lo, Rank mi, Rank hi); //归并算法
  void mergesort(Rank lo, Rank hi); //归并排序
  void selectionsort(Rank lo, Rank hi); //选择排序
   //堆排序
   //轴点构造
   //快速排序
   //希尔排序
  
  //成员变量 ||成员变量结尾加上“_”
  Rank size_; //当前规模 即Rank==n的位置
  int capacity_;  //容量
  T* elem_; //向量数据域本身位置 即Rank==0的位置
}; //Vector