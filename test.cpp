#include <iostream>
#include <list>
#include <iterator>
#include <string>
#include <conio.h>
using namespace std;

/*--------------------------
Test program to teach myself a little C++!
Will be leaving myself little notes as I go for future refreshing.
--------------------------*/

//Ok classes seem very similar, will be using this one to
//define objects to be held in the inventory system
class object{
    public:
        int weight; //Weight for incumberance system
        int amount; //Amount of this type of object held
        string name; //Name of the object
        string description; //Flavor text for the object
        //float value; // Khajiit has wares... May add value to objects later

    // Constructor. Seems to work similarly to java or C# atm... hmmm
    object(int weight, int amount, string name, string description)
    {
        //"this." has different syntax
        this -> weight = weight;
        this -> amount = amount;
        this -> name = name;
        this -> description = description;
    }

    string getName()
    {
        return name;
    }

    void setName(string newName)
    {
        name = newName;
    }

    int getAmount()
    {
        return amount;
    }

    void setAmount(int newAmount)
    {
        amount = newAmount;
    }

    int getWeight()
    {
        return weight;
    }

    void setWeight(int newWeight)
    {
        weight = newWeight;
    }

    string getDescription()
    {
        return description;
    }

    void setDescription(string newDescription)
    {
        description = newDescription;
    }
};

//Taking input for the main menu
int MainMenuInput()
{
    string choice;
    while(true)
    {
        //Take input, then determine if it's a single digit number
        cout << "Chose an option:\n1: Add item.\n2: Remove item.\n3: View list \n4: Exit program\nEnter number:";
        cin >> choice;
        if(choice.size() == 1 && isdigit(choice[0]))
        {
            //cout << choice;
            return stoi(choice);
        }
        else
        {
            cout << "Your choice must be a number between 1 and 4\n";
        }
    } 
    return 0;
}

//Adding an item.
void AddItem(list <object> * items, list <object>  * inventory, int * currentCapacity, int maxCapacity)
{
    //present them with list of objects to pick up.
    list <object> :: iterator it;
    int itemLister = 1;

    cout << "Available objects:\n";
    for(it = (*items).begin(); it != (*items).end(); ++it)
    {
        object temp(0,0,"","");
        temp = *it;
        cout << to_string(itemLister) << ": " << temp.getName() << "\n";
        itemLister++;
    }
    //add selected object from objs to inventory.
    //REMEMBER: Insert function inserts before the position currently pointed at
    //Although the splice function is far more robust so I'll instead use that.
    cout << "Enter the number of an item to add: ";
    string choice;
    cin >> choice;
    if(choice.size() == 1 && isdigit(choice[0]))
    {
        //convert to int from char using ascii
        int iChoice = choice[0] - '0';

        //Check if the int is within the bounds of the selectable items
        if(iChoice > 0 && iChoice < itemLister)
        {
            //cout << "Reached";
            it = items->begin();
            advance(it, (iChoice-1));
            object temp = *it;

            //Check if max carry weight is reached
            if((*currentCapacity + temp.getWeight()) <= maxCapacity)
            {
                *currentCapacity = *currentCapacity + temp.getWeight();
                inventory->splice(inventory->end(), *items, it);
            }
            else
            {
                cout << "Your inventory is too full\n";
            }
        }
        else
        {
            //There is no item of this index
            cout << "That number isn't an item\n";
        }
    }
    else
    {
        cout << "Please enter a number between the given range\n";
    }
}

//Removing an item.
void RemoveItem(list <object> * items, list <object>  * inventory, int * currentCapacity)
{
    //present them with list of objects to pick up.
    list <object> :: iterator it;
    int itemLister = 1;

    cout << "Inventory:\n";
    for(it = (*inventory).begin(); it != (*inventory).end(); ++it)
    {
        object temp(0,0,"","");
        temp = *it;
        cout << to_string(itemLister) << ": " << temp.getName() << "\n";
        itemLister++;
    }
    //add selected object from objs to inventory.
    cout << "Enter the number of an item to remove: ";
    string choice;
    cin >> choice;
    if(choice.size() == 1 && isdigit(choice[0]))
    {
        //convert to int from char using ascii
        int iChoice = choice[0] - '0';

        //Check if the int is within the bounds of the selectable items
        if(iChoice > 0 && iChoice < itemLister)
        {
            it = inventory->begin();
            advance(it, (iChoice-1));
            //It seems you must make a variable to store a copy of the object to access it's functions.
            object temp = *it;
            
            *currentCapacity = *currentCapacity - temp.getWeight();
            items->splice(items->end(), *inventory, it);
        }
        else
        {
            //There is no item of this index
            cout << "That number isn't an item";
        }
    }
    else
    {
        cout << "Please enter a number between the given range";
    }
}


int main(void){
    cout << "Welp, this works.";

    int maxCarryCapacity = 20;
    int carryAmount = 0;

    //Make a list of objects and populate them
    list <object> objs;
    for(int i = 0; i<5; i++)
    {
        object temp(5, 1, "Thing " + to_string(i), "Test object!");
        objs.push_back(temp);
    }
    //Make the list for the users inventory
    list <object> inventory;

    while(true)
    {
        int input;
        //Show the main menu and take input.
        input = MainMenuInput();
        switch(input)
        {
            case 1:
            {
                system("cls"); //only works for windows... will have to find a way to change that.
                cout << "Option 1 selected\n";

                //Passing adresses because pointers are needed to actually edit the original value.
                AddItem(&objs, &inventory, &carryAmount, maxCarryCapacity);
                break;
            }
            case 2:
            {
                system("cls");
                cout << "Option 2 selected\n";

                RemoveItem(&objs, &inventory, &carryAmount);
                break;
            }
            case 3:
            {
                cout << "Option 3 selected\n";
                //Printing out a list for testing.
                if(inventory.empty())
                {
                    cout << "You have nothing in your inventory yet!\n";
                }
                else
                {
                    cout << "Your inventory:\n";
                    //Seems like you have to make an iterator to be able to itterate through a list
                    //Makes sense since it's all pointers.
                    list <object> :: iterator it;
                    for(it = inventory.begin(); it != inventory.end(); ++it)
                    {
                        object temp(0,0,"","");
                        temp = *it;
                        cout << temp.getName() << "\n";
                    }
                }
                break;
            }
            case 4:
            {
                cout << "Exiting program\n";
                return 0;
                break;
            }
            default:
            {
                cout << "Your choice must be a number between 1 and 4\n";
            }
        }
    }
}