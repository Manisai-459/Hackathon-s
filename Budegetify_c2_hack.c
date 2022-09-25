#include <stdio.h>
#include <stdlib.h>
struct borrow
{
    int val;
    int day;
    struct borrow *next;
};
struct items
{
    int val;
    char date[11], item[50];
    struct items *next;
};
struct student
{
    char name[50], roll[15], date[11];
    int limit, balance, day, debt, account_balance;
    struct items *head;
    struct borrow *headb;
};
void day_reminder(struct student *x)
{
    x->day += 1;
    struct borrow *temp = x->headb;
    int d = 0;
    while (temp)
    {
        if (temp->day == 2)
        {
            temp->val += 2;
            temp->day = 0;
        }
        temp->day += 1;
        d += temp->val;
        temp = temp->next;
    }
    if (x->day == 30 && x->debt != 0)
    {
        printf("Today is 30th day\n");
        printf("You need to pay  ' %d '  amount to open your deposit account for next 30 days", d);
    }
}
void purchase(struct student *x)
{
    if (x->day == 0 && x->debt != 0)
        printf("After clearing debt you can deposit and purchase anything\n");
    else
    {
        if (x->balance > 0)
        {
            struct items *temp = (struct items *)malloc(sizeof(struct items));
            fflush(stdin);
            printf("Enter item name : ");
            scanf("%[^\n]s", temp->item);
            printf("Enter price : ");
            scanf("%d", &(temp->val));
            if (temp->val <= x->balance)
            {
                printf("Enter date : ");
                scanf("%s", temp->date);
                x->balance -= temp->val;
                temp->next = x->head;
                x->head = temp;
            }
            else
            {
                free(temp);
                printf("\nYour balance : %d\nYour balance is not sufficent to purchase\n", x->balance);
            }
        }
        else
            printf("no balance in your in your account");
    }
}
void add_money(struct student *x)
{
    if (x->day == 0 && x->debt == 0)
    {
        int n;
        printf("Your previous month balance is : %d\n", x->balance);
        printf("Set limit for 30 days : ");
        scanf("%d", &(x->limit));
        printf("Enter money you want to deposit : ");
        scanf("%d", &n);
        x->balance += n;
        printf("Money deposited\n");
    }
    else
    {
        if (x->account_balance < x->limit && x->day != 30)
        {
            int n;
            printf("Your limit is : %d\n", x->limit);
            printf("Enter amount to deposit : ");
            scanf("%d", &n);
            if ((x->account_balance + n) <= x->limit)
            {
                x->account_balance += n;
                x->balance += n;
            }
            else
                printf("you can only add %d\\- only\n", x->limit - x->account_balance);
        }
        else
        {
            printf("you are remaining with %d\n", x->balance);
            printf("As you reached the limit of this month you need to borrow amount from university\n");
            struct borrow *ptr = (struct borrow *)malloc(sizeof(struct borrow));
            struct items *temp = (struct items *)malloc(sizeof(struct items));
            printf("Enter amount to be added : ");
            scanf("%d", &(temp->val));
            x->balance += temp->val;
            fflush(stdin);
            printf("Enter item name : ");
            scanf("%[^\n]s", temp->item);
            ptr->val = temp->val;
            ptr->day = 0;
            ptr->next = x->headb;
            x->headb = ptr; // ! update boorow items list
            temp->next = x->head;
            x->head = temp; // ! updating items list
        }
    }
}
void get_info(struct student *name)
{
    printf("Enter name : ");
    scanf("%[^\n]s", name->name);
    fflush(stdin);
    printf("Enter roll no : ");
    scanf("%[^\n]s", name->roll);
    fflush(stdin);
    printf("Enter date : ");
    scanf("%[^\n]s", name->date);
    fflush(stdin);
    printf("Set limit of money you want to spend this month : ");
    scanf("%d", &(name->limit));
    printf("Enter money you want to deposit : ");
    scanf("%d", &(name->balance));
    while (name->limit < name->account_balance)
    {
        printf("Warning !: Deposit should be less than set Limit\nThe amount will be refunded\n");
        printf("Please Re-Deposit the money: ");
        scanf("%d", &name->balance);
    }
    name->account_balance = name->balance;
    name->day = 1;
}
void display(struct student *x)
{
    printf("Name : %s\n", x->name);
    printf("Roll no : %s\n", x->roll);
    printf("Limit : %d\n", x->limit);
    printf("Balance left : %d\n", x->balance);
    printf("Debt = %d\n", x->debt);
    printf("Day of deposit : %s\n", x->date);
}
void items_purchased(struct student *x)
{
    if (x->head == NULL)
        printf("No items purchased\n");
    else
    {
        printf("List of items spent till date\n");
        struct items *temp = x->head;
        while (temp)
        {
            printf("%s\t%s\t%d\n", temp->item, temp->date, temp->val);
            temp = temp->next;
        }
    }
}

void clear_debt(struct student *x)
{
    if (x->headb == NULL)
        printf("\nNo borrow taken from university \n");
    else
    {
        int sum = 0, i;
        struct borrow *temp = x->headb;
        while (temp)
        {
            sum += temp->val;
            temp = temp->next;
        }
        printf("Amount needed to pay : %d\n", sum);
        printf("Enter amount to be paid (you need to pay full amount) : ");
        scanf("%d", &i);
        if (i == sum)
        {
            printf("Your debt is clear\n");
            struct borrow *temp = x->headb, *ptr = x->headb;
            while (temp)
            {
                ptr = temp;
                temp = temp->next;
                free(ptr);
            }
            x->headb = NULL;
        }
    }
}

int main()
{
    struct student *x = (struct student *)malloc(sizeof(struct student));
    x->headb = NULL;
    x->head = NULL;
    x->debt = 0;
    int n;
    get_info(x);
    do
    {
        printf("\n1.Add money\n");
        printf("2.Purchase\n");
        printf("3.Get my account info\n");
        printf("4.List of item purchased\n");
        printf("5.If date changed\n");
        printf("6.Clear debt\n");
        printf("enter choise : ");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            add_money(x);
            break;
        case 2:
            purchase(x);
            break;
        case 3:
            display(x);
            break;
        case 4:
            items_purchased(x);
            break;
        case 5:
            day_reminder(x);
            break;
        case 6:
            clear_debt(x);
        default:
            printf("Enter correct choise : ");
            break;
        }
    } while (1);
    return 0;
}