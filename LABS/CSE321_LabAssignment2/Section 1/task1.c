#include <stdio.h>

struct Item {
    int quantty;
    int unitprice_each;
};

int main() {
    struct Item paratha, vegetable, water;
    int sumof_people;
    float sumof_cost=0, cost_perperson;

    // Paratha input nilam
    printf("Quantity Of Paratha: ");
    scanf("%d", &paratha.quantty);
    printf("Unit Price: ");
    scanf("%d", &paratha.unitprice_each);

    //Vegetable input nilam
    printf("Quantity Of Vegetables: ");
    scanf("%d", &vegetable.quantty);
    printf("Unit Price: ");
    scanf("%d", &vegetable.unitprice_each);

    //Mineral Water input nilam
    printf("Quantity Of Mineral Water: ");
    scanf("%d", &water.quantty);
    printf("Unit Price: ");
    scanf("%d", &water.unitprice_each);

    printf("Number of People: ");
    scanf("%d", &sumof_people);

    float paratha_cost= paratha.quantty* paratha.unitprice_each; 
    float vegetable_cost= vegetable.quantty * vegetable.unitprice_each; 
    float water_cost = water.quantty* water.unitprice_each; 
    
    sumof_cost = paratha_cost + vegetable_cost + water_cost; 
    cost_perperson = sumof_cost / sumof_people;

   
    printf("Individual people will pay: %.2f tk\n", cost_perperson);

    return 0;
}
	
