#include <iostream>
using namespace std;

// initialization
class Poly {
public:
    int coefficient;
    int exponent;
    Poly* next;
    Poly(int coef, int exp);
};

class Linked_List {
public:
    Poly* head;
    Linked_List();

    void insert_term(int coefficient, int exponent); // sort
    Linked_List multiply(const Linked_List& other);   // multiplication
    void display();                                 // cout
};

int main() {
    Linked_List poly1, poly2;
    int num_terms, coef, exp;

    // Input for the first polynomial
    do {
        cout << "Enter the number of terms for the first polynomial: ";
        cin >> num_terms;
        if (num_terms < 0) {
            cout << "Negative numbers cannot be entered, please re-enter" << endl; 
        }
    } while (num_terms < 0);

    for (int i = 0; i < num_terms; ++i) {
        cout << "Enter number " << i + 1 << " coefficients and exponents of terms: ";
        cin >> coef >> exp;
        poly1.insert_term(coef, exp);
    }

    // Input for the second polynomial
    do {
        cout << "Enter the number of terms for the second polynomial: ";
        cin >> num_terms;
        if (num_terms < 0) {
            cout << "Negative numbers cannot be entered, please re-enter" << endl; 
        }
    } while (num_terms < 0);

    for (int i = 0; i < num_terms; ++i) {
        cout << "Enter number " << i + 1 << " coefficients and exponents of terms: ";
        cin >> coef >> exp;
        poly2.insert_term(coef, exp);
    }

    Linked_List result = poly1.multiply(poly2);
    cout << "The polynomial result after multiplication is: ";
    result.display();

    return 0;
}

// constructor
Poly::Poly(int coef, int exp) : coefficient(coef), exponent(exp), next(nullptr) {}

Linked_List::Linked_List() : head(nullptr) {}

void Linked_List::insert_term(int coefficient, int exponent) {
    if (coefficient == 0) return; // ignore 0 coefficients

    Poly* new_node = new Poly(coefficient, exponent);
    if (!head || head->exponent < exponent) {
        // insert head
        new_node->next = head;
        head = new_node;
    } 
    else { // sort
        Poly* current = head;
        Poly* prev = nullptr;
        while (current && current->exponent > exponent) {
            prev = current;
            current = current->next;
        }

        if (current && current->exponent == exponent) {
            // Combine terms with the same index
            current->coefficient += coefficient;
            if (current->coefficient == 0) {
                // delete 0 coefficient
                if (prev) prev->next = current->next;
                else head = current->next;
                delete current;
            }
            delete new_node;
        } else {
            // insert
            new_node->next = current;
            if (prev) prev->next = new_node;
            else head = new_node;
        }
    }
}

Linked_List Linked_List::multiply(const Linked_List& other) {
    Linked_List result;
    for (Poly* ptr1 = head; ptr1 != nullptr; ptr1 = ptr1->next) {
        for (Poly* ptr2 = other.head; ptr2 != nullptr; ptr2 = ptr2->next) {
            // Multiply coefficients
            int new_coefficient = ptr1->coefficient * ptr2->coefficient;
            // Adding exponents
            int new_exponent = ptr1->exponent + ptr2->exponent;
            result.insert_term(new_coefficient, new_exponent);
        }
    }
    return result;
}

void Linked_List::display() {
    if (!head) {
        cout << "0" << endl;
        return;
    }
    
    Poly* current = head;
    bool first = true;

    while (current) {
        // Output operation symbols
        if (!first && current->coefficient > 0) cout << " + ";
        
        if (current->coefficient < 0) cout << " - ";
        else if (!first) cout << " ";

        cout << abs(current->coefficient);
        
        // Exponent not 0 output 'x'
        if (current->exponent != 0) cout << "x^" << current->exponent;

        current = current->next;
        first = false;
    }
    
    cout << endl;
}