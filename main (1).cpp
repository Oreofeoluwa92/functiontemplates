#include <iostream>
#include <vector>
#include <string>

template <class T>
using ELEM = std::vector<T>;

template <class T>
using VEC = std::vector<ELEM<T>>;

template <class T>
using action_t = T (*)(int);

template <class T>
using pred_t = bool (*)(T);

template <class T>
using map_t = T (*)(T, T);

//printElem
template <class T>
void printElem(const ELEM<T> &v) {
	for ( auto &elem : v) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;
}

//initVec
template <class T>
void initVec(VEC<T> &v, ELEM<T> &&cons) {
	v.push_back(cons);
}

//printVec
template <class T>
void printVec(VEC<T> &v) {
    std::cout << "[ ";
    for (size_t i = 0; i < v.size(); ++i) {
        for (size_t j = 0; j < v[i].size(); ++j) {
            std::cout << v[i][j];
            if (j != v[i].size() - 1) {
                std::cout << " , ";
            }
        }
       
    }
    std::cout << " ]\n";
}


//generate
template <class T>
VEC<T> generate(int N, action_t<T>f) {
	VEC<T> result;
	ELEM<T> elem;
	for (int i = 0; i < N; ++i) {
		elem.push_back(f(i));
	}
	result.push_back(elem);
	return result;
}
//zip
template <class T>
VEC<T> zip(VEC<T>&v,VEC<T>& w) {
	VEC<T> result;

	for (int i = 0; i < v.size(); ++i) {
		ELEM<T>elem;
		for (int j = 0; j < w[i].size(); ++j) {
			elem.push_back(v[i][j]);
			elem.push_back(w[i][j]);
			
		}
		result.push_back(elem);
		
	}

	return result;
}
//filter
template <class T>
VEC<T> filter(VEC<T>&v, pred_t<T>f) {
	VEC<T> result;
	ELEM<T> elem;
	for (auto& e : v[0]) {
		if (f(e)) elem.push_back(e);
	}
	result.push_back(elem);
	return result;
}
//map
template <class T>
VEC<T> map(VEC<T>&v, action_t<T>f) {
	VEC<T> result;
	ELEM<T> elem;
	for (auto& e : v[0]) {
		elem.push_back(f(e));
	}
	result.push_back(elem);
	return result;
}

//reduce
template <class T>
ELEM<T> reduce(VEC<T>&v, map_t<T>f, ELEM<T>ident) {
	ELEM<T> result = ident;
	for (auto& e : v[0]) {
		result[0] = f(result[0], e);
	}
	return result;
}

// Functions for testing
int f (int x) {
	return x * x;

}
int h(int i) {
	return i > 0 ? 1 : 0;
}

template <class T>
T k(T a, T b) {
	return a + b;
}
bool g(int i) {
	return i>0;
}


int main() {
	VEC<int> v;
	initVec(v, ELEM<int> {1, 2, 3, 4});
	VEC<int> w;
	initVec(w, ELEM<int> {-1, 3, -3, 4});
	printVec(v);
	std::cout << std::string(10, '*') << std::endl;
	printVec(w);
	std::cout << std::string(10, '*') << std::endl;



	VEC<int> z = zip(v, w);
	printVec(z);
	std::cout << std::string(10, '*') << std::endl;

	VEC<int> x = zip(z,z);
	printVec(x);
	std::cout << std::string(10, '*') << std::endl;

	VEC<int> a = generate(10, f);
	printVec(a);
	std::cout << std::string(10, '*') << std::endl;

	VEC<int> y = filter(w, g);
	printVec(y);
	std::cout << std::string(10, '*') << std::endl;

	VEC<int> u = map(w, h); // h is like g but returns 1 or 0
	printVec(u);
	std::cout << std::string(10, '*') << std::endl;

	ELEM<int> e = reduce(u, k, ELEM<int> {0});
	printElem(e);

	std::cout << std::endl << std::string(10, '$') << std::endl;
	VEC<std::string> ws;
	initVec(ws, ELEM<std::string> {"hello", "there", "franco", "carlacci"});
	printVec(ws);
	ELEM<std::string> es = reduce(ws, k, ELEM<std::string> {""});
	printElem(es);

	VEC<char> wc;
	initVec(wc, ELEM<char> {'a', 'b', 'c', 'd'});
	std::cout << std::endl << std::string(10, '$') << std::endl;
	printVec(wc);
	ELEM<char> ec = reduce(wc, k, ELEM<char> {' '});
	std::cout << std::endl << std::string(10, '$') << std::endl;
	printElem(ec);

	return 0;
}
