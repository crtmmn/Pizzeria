#include <iostream>
#include <vector>

using namespace std;

class Ingredient {
private:
    string name;
    int quantity;
    float calories;
public:
    Ingredient(string ingredientName, int ingredientQuantity, float ingredientCalories) {
        name = ingredientName;
        quantity = ingredientQuantity;
        calories = ingredientCalories;
    }
    string getName() {
        return name;
    }
    int getQuantity() {
        return quantity;
    }
    float getCalories() {
        return calories;
    }

};
class Pizza {
private:
    string name;
    string dough;
    string sauce;
    float price;
    vector<Ingredient*> toppings;
public:
    float getCalories() {
        float sumOfCalories = 0;
        for(auto it = toppings.begin(); it!= toppings.end(); it++) {
            sumOfCalories += (*it)->getCalories();
        }
        return sumOfCalories;
    }
    void setName(string pizzaName) {
        name = pizzaName;
    }
    void setDough(string pizzaDough) {
        dough = pizzaDough;
    }
    void setSauce(string pizzaSauce) {
        sauce = pizzaSauce;
    }
    void setToppings(vector<Ingredient*> listOfToppings) {
        for(auto it = listOfToppings.begin(); it != listOfToppings.end(); it++) {
            toppings.push_back(*it);
        }
    }
    void displayPizza() {
        cout << "Pizza name: " << name << endl;
        cout << "Pizza dough: " << dough << endl;
        cout << "Pizza sauce: " << sauce << endl;
        cout << "Toppings: ";
        if(toppings.size() == 0) {
            cout << "Without toppings" << endl;
        }
        for(int i = 0; i < toppings.size(); i++) {
            if(i == toppings.size()-1) {
                cout << toppings[i]->getName() << endl;
            }
            else {
                cout << toppings[i]->getName() << ", ";
            }
        }
        cout << "Calories: " << getCalories() << endl;
    }
};

class PizzaBuilder {
protected:
    Pizza* pizza;
public:
    virtual void createNewPizza() {
        pizza = new Pizza();
    }
    virtual void buildName() = 0;
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void addToppings() = 0;
    virtual Pizza* getPizza() {
        return pizza;
    }
};

class MargheritaBuilder : public PizzaBuilder {
public:
    void buildName() {
        pizza->setName("Margherita");
    }
    void buildDough() {
        pizza->setDough("Neapolitan");
    }
    void buildSauce() {
        pizza->setSauce("Tomato");
    }
    void addToppings() {
        vector<Ingredient*> listOfToppings;
        Ingredient* mozarella = new Ingredient("Mozarella", 1, 200.0);
        Ingredient* oil = new Ingredient("Oil", 1, 800.0);
        listOfToppings.push_back(mozarella);
        listOfToppings.push_back(oil);
        pizza->setToppings(listOfToppings);
    }
};

class PepperoniBuilder : public PizzaBuilder {
public:
    void buildName() {
        pizza->setName("Pepperoni");
    }
    void buildDough() {
        pizza->setDough("New York Style");
    }
    void buildSauce() {
        pizza->setSauce("Tomato");
    }
    void addToppings() {
        vector<Ingredient*> listOfToppings;
        Ingredient* kabanos = new Ingredient("Kabanos", 1, 320.0);
        Ingredient* chili  = new Ingredient("Chili", 1, 40.0);
        listOfToppings.push_back(kabanos);
        listOfToppings.push_back(chili);
        pizza->setToppings(listOfToppings);
    }
};

class PizzaFactory {
private:
    PizzaBuilder* pizzaBuilder;
public:
    void setPizzaBuilder(PizzaBuilder* pb) {
        pizzaBuilder = pb;
    }
    Pizza* getPizza() {
        return pizzaBuilder->getPizza();
    }
    void constructPizza() {
        pizzaBuilder->createNewPizza();
        pizzaBuilder->buildName();
        pizzaBuilder->buildDough();
        pizzaBuilder->buildSauce();
        pizzaBuilder->addToppings();
    }
};

class CustomPizzaBuilder : public PizzaBuilder {
private:
    vector<Ingredient*> customToppings;
public:
    CustomPizzaBuilder() {
        customToppings.push_back(new Ingredient("Onion", 1, 40.0));
        customToppings.push_back(new Ingredient("Bacon", 1, 500.0));
        customToppings.push_back(new Ingredient("Chicken", 1, 200.0));
        customToppings.push_back(new Ingredient("Paprika", 1, 20.0));
        customToppings.push_back(new Ingredient("Feta", 1, 250.0));
    }
    void buildName() {
        cout << "Enter custom pizza name: ";
        string customName;
        cin >> customName;
        pizza->setName(customName);
    }
    void buildDough() {
        cout << "Enter custom pizza dough: ";
        string customDough;
        cin >> customDough;
        pizza->setDough(customDough);
    }
    void buildSauce() {
        cout << "Enter custom pizza sauce: ";
        string customSauce;
        cin >> customSauce;
        pizza->setSauce(customSauce);
    }
    void addToppings() {
        vector<Ingredient*> listOfToppings;
        cout << "Toppings that you can choose:" << endl;
        for(int i = 0; i < customToppings.size(); i++) {
            cout << i << ": " << customToppings[i]->getName() << endl;
        }
        cout << "Quantity of toppings (Max 5): ";
        int quantityToppings;
        cin >> quantityToppings;
        if(quantityToppings > 5) {
            quantityToppings = 5;
            cout << "You chose too much toppings, quantity of toppings was reduced to 5" << endl;
        }
        for(int i = 0; i < quantityToppings; i++) {
            cout << "Choose topping: ";
            int choice;
            cin >> choice;
            if(choice >= 0 && choice < customToppings.size()) {
                listOfToppings.push_back(customToppings[choice]);
            }
            else {
                cout << "Incorrect choice" << endl;
            }
        }
        pizza->setToppings(listOfToppings);
    }
};

int main()
{
    PizzaFactory pizzaFactory;
    cout << "Choose pizza: " << endl;
    cout << "#1 Margherita" << endl;
    cout << "#2 Pepperoni" << endl;
    cout << "#3 Custom pizza" << endl;
    int choice;
    cout << "Your choice: ";
    cin >> choice;
    if(choice == 1) {
        PizzaBuilder* margheritaBuilder = new MargheritaBuilder();
        pizzaFactory.setPizzaBuilder(margheritaBuilder);
        pizzaFactory.constructPizza();
        Pizza* margheritaPizza = pizzaFactory.getPizza();
        margheritaPizza->displayPizza();
    }
    else if(choice == 2) {
        PizzaBuilder* pepperoniBuilder = new PepperoniBuilder();
        pizzaFactory.setPizzaBuilder(pepperoniBuilder);
        pizzaFactory.constructPizza();
        Pizza* pepperoniPizza = pizzaFactory.getPizza();
        pepperoniPizza->displayPizza();
    }
    else if(choice == 3) {
        CustomPizzaBuilder* customBuilder = new CustomPizzaBuilder();
        pizzaFactory.setPizzaBuilder(customBuilder);
        pizzaFactory.constructPizza();
        Pizza* customPizza = pizzaFactory.getPizza();
        customPizza->displayPizza();
    }
    else {
        cout << "Incorrect choice" << endl;
    }
    return 0;
}
