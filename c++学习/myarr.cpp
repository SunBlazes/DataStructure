#include<iostream>
using namespace std;

template<typename T>
class MyArray {
	private:
		T *array;
		int length;
		int size;
	public:
		MyArray(int size) {
			array = new T[size];
			this->size = size;
			length = 0;
		}
		MyArray(const MyArray<T> &obj) {
			this->size = obj.size;
			this->length = obj.length;
			if (obj.array != NULL) {
				array = new T[size];
				int i = 0;
				for (; i < length; i++) {
					array[i] = obj.array[i];
				}
			}
		}
		MyArray& operator=(const MyArray<T> &obj) {
			this->length = obj.length;
			this->size = obj.size;
			if (array != NULL) {
				delete array;
				array = NULL;
			}
			if (obj.array != NULL) {
				array = new T[size];
				int i = 0;
				for (; i < length; i++) {
					array[i] = obj.array[i];
				}
			}
			return *this;
		}
		~MyArray() {
			if (array != NULL) {
				delete array;
				array = NULL;
			}
			this->length = 0;
			this->size = 0;
		} 
		T operator[](int loca) {
			if (loca >= this->length) {
				cout<<"超出数组现有长度\n"; 
				return -1;
			} else {
				return array[loca];
			}
		}
		void Insert_Tail(T data) {
			if (length == size) {
				cout<<"插入失败，容量已满\n";
			} else {
				this->array[length++] = data;
			}
		}
		T Delete_Tail() {
			if (length == 0) {
				cout<<"数组为空，不能删除\n";
				return -1;
			} else {
				return array[--length];
			}
		}
		int Size() {
			return size;
		}
		int Length() {
			return length;
		}
};

main () {
	MyArray<int> obj(1);
	obj.Insert_Tail(555);
	MyArray<int> obj1 = obj;
	cout<<obj1.Length()<<endl;
	cout<<obj1[obj1.Length() - 1]<<endl;
	MyArray<int> obj2(5);
	obj2.Insert_Tail(55);
	obj2.Insert_Tail(10);
	obj = obj2;
	cout<<obj[0];
	return 0; 	
}
