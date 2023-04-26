#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct Product {
    string name;
    int price;
    int discount;
    string barcode;
};

class Store {
public:
    void addProduct(string barcode, string name, int price, int discount) {
        Product product;
        product.name = name;
        product.price = price;
        product.discount = discount;
        product.barcode  = barcode;
        products.insert(make_pair(barcode,product));
    }
    Product getProduct(string barcode) {
        return products[barcode];
    }
private:
    map<string, Product> products;
};

class CashBox {
public:

    CashBox(Store store) {
        this->store = store;
    }

    string scanProduct(string barcode) {
        Product product;
        product = store.getProduct(barcode);
        return (" scanned product: " + product.name + " price: " + to_string(product.price)); // ведь касса выводит данные о каждом сканированном товаре! логично, сканированный продукт должен добавляться в чек, но я прибавил возврат данных товара, иначе, в сканировании не вижу большого смысла
    }

    string getDescription(string barcode) {
        return " name: " + store.getProduct(barcode).name + " price: " + to_string(store.getProduct(barcode).price) + " barcode: " + store.getProduct(barcode).barcode + " discount " + to_string(store.getProduct(barcode).discount);
    }

    void addProduct(string barcode) {
        if (cashBoxProducts.count(barcode)) {
            cashBoxProducts[barcode] += 1;
        }
        else {
            cashBoxProducts.insert(make_pair(barcode, 1));
        }
    }

    void removeProduct(string barcode) {
        if (cashBoxProducts.count(barcode)) {
            cashBoxProducts.erase(barcode);
        }
    }

    int getTotalPrice() {
        int totalPrice = 0;
        for (auto& item : cashBoxProducts) {
            totalPrice += store.getProduct(item.first).price * item.second;
        }
        return totalPrice;
    }
    int getTotalDiscount() {
        int discount = 0;
        for (auto& item : cashBoxProducts) {
            discount += (int)(store.getProduct(item.first).price * item.second * ((double)(store.getProduct(item.first).discount) / 100.0));
        }
        return discount;
    }
    int getFinalPrice() {
        return getTotalPrice() - getTotalDiscount();
    }
    void printCheck() {
        cout << "\n Store check" << endl;
        for (auto& item : cashBoxProducts) {
            cout << " name: " + store.getProduct(item.first).name + " price: " + to_string(store.getProduct(item.first).price) + " how many: " + to_string(item.second) + " total price of product: " + to_string((store.getProduct(item.first).price) * (item.second)) << endl;
        }
        cout << "\n Total price: " << getTotalPrice() << endl;
        cout << " Discount: " << getTotalDiscount() << endl;
        cout << " Final price: " << getFinalPrice() << endl;
    }
private:
    map<string, int> cashBoxProducts;
    Store store;
};

int main() {
    Store store;

    store.addProduct("0001", "Apple", 200, 10);
    store.addProduct("0002", "Meat", 500, 5);
    store.addProduct("0003", "Chocolate", 120, 20);

    CashBox cashBox(store);

    cout << cashBox.getDescription("0002") << endl;

    cout << cashBox.scanProduct("0002") << endl;
    cashBox.addProduct("0002");
    cout << cashBox.scanProduct("0001") << endl;
    cashBox.addProduct("0001");
    cout << cashBox.scanProduct("0002") << endl;
    cashBox.addProduct("0002");
    cout << cashBox.scanProduct("0003") << endl;
    cashBox.addProduct("0003");

    cashBox.removeProduct("0001");
    cashBox.printCheck();

    system("PAUSE");
    return 0;
}