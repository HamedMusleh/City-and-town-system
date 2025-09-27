#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node *district;
typedef struct node2 *town;
struct node
{
    char d[25];
    int total_p;
    district nextdistrict;
    district prev;
    town next;
};
struct node2
{
    char t[25];
    int popTown;
    town nextT;
    town prevT;
    district prevDistrict;
};

int checkDistrict = 0;
int checkTown = 0;
void display();
void printTown_forFile(district , FILE *);
void printTown(district );
town findTown(district , char *);
int populationOfList(district);
int populationOfDistrict(district);
town getMaxTownInDistrict(district);
town getMinTownInDistrict(district);
void maxTown(district);
void minTown(district);
void deleteTown(district , char *);
void deleteAllTownInDistrict(district);
void printAfterSorting(district);
void insertDistrict(district , char *);
void insertDistrict_new(district , char *, char *, int);
int getSize(struct node *);
void insertTown(district, char *, int);
void printTown(district);
void printListBeforeSort(district);
int getSize(district);
void sortDistrict(district);
district findDistrict(district , char *);
void sortTown(district);
void cutLine(char *, district);
town makeEmpty_Town(town t)
{
    t = (town)malloc(sizeof(struct node2));
    if (t == NULL)
    {
        printf("out of the memory");
    }
    t->prevT = NULL;
    t->nextT = NULL;
    t->prevDistrict = NULL;
    return t;
}
district makeEmpty(district l)
{
    l = (district)malloc(sizeof(struct node));
    if (l == NULL)
    {
        printf("out of the memory");
    }
    l->prev = NULL;
    l->nextdistrict = NULL;
    l->next = NULL;
    return l;
}

int main()
{
    char dis[50];
    char townname[50];
    int population;
    char get;
    struct node *l = makeEmpty(NULL);
    int op;
    char line[500][50];
    FILE *in;
    FILE *out;
    in = fopen("districts.txt", "r");
    printf("enter the operation\n\n");
    display();
    scanf("%d", &op);
    int i = 0;
    while (op != 14)
    {
        int count = 0;
        int newNumber;
        char str[50];
        district p;
        district find;
        if(in == NULL)
        {
            printf("Empty file\n");
            break;
        }
        switch (op)
        {
        case 1:
            while (fgets(str, sizeof(str), in) != NULL)
            {
                strncpy(line[i], str, 50);
                cutLine(str, l);
                i++;
            }
            fclose(in);
            break;
        case 2:
            if (l->nextdistrict == NULL)
            {
                printf("\nyou must load the information\n");
                break;
            }
            // print loaded info
            while (count < i)
            {
                printf("%s", line[count]);
                count++;
            }
            printf("\n");
            break;
        case 3:
            if (l->nextdistrict == NULL)
            {
                printf("\nyou must loaded the information\n");
                break;
            }
            checkDistrict++;
            sortDistrict(l);
            break;
        case 4:
            if (l->nextdistrict == NULL)
            {
                printf("\nyou must loaded the information\n");
                break;
            }
            checkTown++;
            p = l->nextdistrict;
            while (p != NULL)
            {
                sortTown(p);
                p = p->nextdistrict;
            }

            break;
        case 5:
            if (l->nextdistrict == NULL)
            {
                printf("\nyou must loaded the information\n");
                break;
            }
            else if(checkDistrict > 0 && checkTown > 0)
                printAfterSorting(l);
            else
                printf("\nyou must sort the information\n");

            break;
        case 6:
            if (l->nextdistrict == NULL)
            {
                printf("\nyou must loaded the information\n");
                break;
            }
            printf("\nenter the new district : \n");
            scanf("%c", &get);
            // To read from keyboard when the user run it
            fgets(dis, sizeof(dis), stdin);

            dis[strlen(dis) - 1] = '\0';
            if (findDistrict(l, dis) == NULL)
            {
                // insert the new district then sort the list
                insertDistrict(l, dis);
                sortDistrict(l);
            }
            else
                printf("\ndistrict in the list : %s\n", dis);
            break;
        case 7:
            if (l->nextdistrict == NULL)
            {
                printf("\nyou must loaded the information\n");
                break;
            }
            printf("\nenter the certain district : \n");
            scanf("%c", &get);
            fgets(dis, sizeof(dis), stdin);
            dis[strlen(dis) - 1] = '\0';
            find = findDistrict(l, dis);
            if (find != NULL)
            {
                //insert the new town for a certain district then sort the town
                printf("\nenter the new town : \n");
                fgets(townname, sizeof(townname), stdin);
                townname[strlen(townname) - 1] = '\0';
                printf("\nenter the population : \n");
                scanf("%d", &population);
                insertTown(find, townname, population);
                sortTown(find);
            }
            else
                printf("\nthe %s dose not exit\n", dis);
            break;
        case 8:
            if (l->nextdistrict == NULL)
            {
                printf("you must loaded the information\n");
                break;
            }
            printf("enter the district name to delete town : \n");
            scanf("%c", &get);
            fgets(dis, sizeof(dis), stdin);
            dis[strlen(dis) - 1] = '\0';
            find = findDistrict(l, dis);
            if (find != NULL)
            {
                // delete a town from district
                printf("\nenter the name of the Town you wanted to delete it : \n");
                fgets(townname, sizeof(townname), stdin);
                townname[strlen(townname) - 1] = '\0';
                deleteTown(find, townname);
            }
            else
                printf("\nthis district %s not founded\n", dis);
            break;
        case 9:
            if (l->nextdistrict == NULL)
            {
                printf("\nyou must loaded the information\n");
                break;
            }
            printf("enter the district name to it : \n");
            scanf("%c", &get);
            fgets(dis, sizeof(dis), stdin);
            dis[strlen(dis) - 1] = '\0';
            find = findDistrict(l, dis);
            if (find != NULL)
            {
                //find the district then delete all town
                printf("\nyou must to delete all town in this district\n");
                deleteAllTownInDistrict(find);
                if (find->nextdistrict != NULL)
                    find->nextdistrict->prev = find->prev;
                find->prev->nextdistrict = find->nextdistrict;
                free(find);
            }
            else
                printf("\nthe district %s not exist \n", dis);
            break;
        case 10:
            if (l->nextdistrict == NULL)
            {
                printf("\nyou must loaded the information\n");
                break;
            }
            printf("\nPopulation of palestine = %d \n", populationOfList(l));
            maxTown(l);
            minTown(l);
            break;
        case 11:
            if (l->nextdistrict == NULL)
            {
                printf("\nyou must loaded the information\n");
                break;
            }
            p = l->nextdistrict;
            while (p != NULL)
            {
                p->total_p = populationOfDistrict(p);
                printf("\n%s and the total population = %d\n", p->d, p->total_p);
                p = p->nextdistrict;
            }
            break;
        case 12:
            if (l->nextdistrict == NULL)
            {
                printf("\nyou must loaded the information\n");
                break;
            }
            printf("enter the district name : \n");
            scanf("%c", &get);
            fgets(dis, sizeof(dis), stdin);
            dis[strlen(dis) - 1] = '\0';
            find = findDistrict(l, dis);
            if (find != NULL)
            {
                printf("\n\nenter the name of the town you wanted to change the population : \n");
                fgets(townname, sizeof(townname), stdin);
                townname[strlen(townname) - 1] = '\0';
                find = findDistrict(l, dis);
                town findT = findTown(find, townname);
                if (findT != NULL)
                {
                    printf("enter the new number of population :\n");
                    scanf("%d", &newNumber);
                    findT->popTown = newNumber;
                    sortTown(find);
                }
            }
            else
                printf("\nthis district %s dose not exist\n",dis);
            break;
        case 13:
            if (l->nextdistrict == NULL)
            {
                printf("\nyou must loaded the information\n");
                break;
            }
            out = fopen("sorted_districts.txt", "w");
            p = l->nextdistrict;
            while (p != NULL)
            {
                fprintf(out, "%s a District, Population = %d\n", p->d, populationOfDistrict(p));
                printTown_forFile(p, out);
                p = p->nextdistrict;
            }
            fclose(out);
            break;
        default:
            printf("\ntry agin\n");
            break;
        }
        printf("\nenter the operation\n\n");
        display();
        scanf("%d", &op);
    }
    return 0;
}

void printTown_forFile(district l, FILE *out)
{
    town i;
    i = l->next;
    if (i == NULL)
    {
        printf("%s||\n", l->d);
        return;
    }
    while (i->nextT != NULL)
    {
        if (i->nextT == NULL)
        {
            break;
        }
        i = i->nextT;
    }
    while (i != NULL)
    {
        fprintf(out, "%s ,%d\n", i->t, i->popTown);
        i = i->prevT;
    }
}

town findTown(district l, char *name)
{
    town temp;
    temp = l->next;
    if (temp == NULL)
    {
        printf("There is no town \n");
        return NULL;
    }
    while (temp != NULL)
    {
        if (strcmp(temp->t, name) == 0)
        {
            return temp;
        }
        temp = temp->nextT;
    }
    return NULL;
}

void deleteAllTownInDistrict(district l)
{
    town temp;
    temp = l->next;
    // there is no town in district
    if (temp == NULL)
    {
        l->prev->nextdistrict = l->nextdistrict;
        if(l->nextdistrict != NULL)
            l->nextdistrict->prev = l->prev;
        free(l);
        return;
    }
    // to reach the last town
    while (temp->nextT != NULL)
    {
        temp = temp->nextT;
    }
    // delete town prev
    while (temp->prevT != NULL)
    {
        temp = temp->prevT;
        free(temp->nextT);
        temp->nextT = NULL;
    }
    free(temp);
    l->next = NULL;
}

void maxTown(district l)
{
    district i;
    town max;
    i = l->nextdistrict;
    max = i->next;
    while (max == NULL)
    {
        i = i->nextdistrict;
        max = i->next;
    }
    i = l;
    if (l == NULL)
    {
        printf("there is no linked list\n");
        return;
    }
    if (i->nextdistrict == NULL)
    {
        printf("there is no district in the list\n");
        return;
    }
    while (i->nextdistrict != NULL)
    {
        i = i->nextdistrict;
        town p = getMaxTownInDistrict(i);
        if (p == NULL)
            continue;
        if (p->popTown > max->popTown)
        {
            max = p;
        }
    }
    printf("the max town is : %s with population %d\n", max->t, max->popTown);
}

void minTown(district l)
{
    district i;
    town min;
    i = l->nextdistrict;
    min = i->next;
    while (min == NULL)
    {
        i = i->nextdistrict;
        min = i->next;
    }
    i = l;
    if (l == NULL)
    {
        printf("there is no linked list\n");
        return;
    }
    if (i->nextdistrict == NULL)
    {
        printf("there is no district in the list\n");
        return;
    }
    while (i->nextdistrict != NULL)
    {
        i = i->nextdistrict;
        town p = getMinTownInDistrict(i);
        if (p == NULL)
            continue;
        if (p->popTown < min->popTown)
            min = p;
    }
    printf("the min town is : %s with population %d", min->t, min->popTown);
}

town getMinTownInDistrict(district d)
{
    town min = makeEmpty_Town(NULL);
    if (d->next == NULL)
    {
        return NULL;
    }
    min = d->next;
    town ptr;
    ptr = d->next->nextT;
    while (ptr != NULL)
    {
        if (ptr->popTown < min->popTown)
        {
            min = ptr;
        }
        ptr = ptr->nextT;
    }
    return min;
}

town getMaxTownInDistrict(district d)
{
    town max = makeEmpty_Town(NULL);
    max = d->next;
    town ptr;
    if (d->next == NULL)
        return NULL;
    ptr = d->next->nextT;
    if (ptr == NULL)
        return max;
    while (ptr != NULL)
    {
        if (ptr->popTown > max->popTown)
        {
            max = ptr;
        }
        ptr = ptr->nextT;
    }
    return max;
}

void deleteTown(district l, char *nameTown)
{
    town ptr = l->next;
    town ptr2 = l->next;
    while (ptr2 != NULL)
    {
        if (strcmp(ptr2->t, nameTown) == 0)
        {
            if (ptr->prevT == NULL)
            {
                l->next = ptr->nextT;
                if(ptr->nextT != NULL)
                {
                    ptr->nextT->prevT = ptr->prevT;
                    ptr->nextT->prevDistrict = l;
                }
                free(ptr2);
                printf("\n%s has been deleted\n",ptr2->t);
                return;
            }
            ptr = ptr->prevT;
            if (ptr2->nextT != NULL)
                ptr2->nextT->prevT = ptr;
            ptr->nextT = ptr2->nextT;
            printf("\n%s has been deleted\n",ptr2->t);
            free(ptr2);
            return;
        }
        ptr = ptr->nextT;
        ptr2 = ptr2->nextT;
    }
    printf("the town %s dose not exist\n",nameTown);
}

int populationOfList(district l)
{
    int total = 0;
    district p;
    p = l;
    if (l == NULL)
    {
        printf("there is no linked list\n");
        return total;
    }
    if (p->nextdistrict == NULL)
    {
        printf("there is no district in the list\n");
        return total;
    }
    while (p->nextdistrict != NULL)
    {
        p = p->nextdistrict;
        total += populationOfDistrict(p);
        p->total_p = total;
    }
    return total;
}

int populationOfDistrict(district d)
{
    int total = 0;
    town ptr;
    ptr = d->next;
    if (d->next == NULL)
        return total;
    while (ptr != NULL)
    {
        total += ptr->popTown;
        ptr = ptr->nextT;
    }
    return total;
}

void addNewTown(district l, char *nameDis, char *nameTown, int population)
{
    district temp;
    temp = l;
    while (temp->nextdistrict != NULL)
    {
        temp = temp->nextdistrict;
        if (strcmp(temp->d, nameDis) == 0)
        {
            insertTown(temp, nameTown, population);
        }
    }
}

district findDistrict(district l, char *nameDis)
{
    district temp;
    temp = l;
    while (temp->nextdistrict != NULL)
    {
        temp = temp->nextdistrict;
        if (strcmp(temp->d, nameDis) == 0)
        {
            return temp;
        }
    }
    return NULL;
}

void display()
{
    printf("1. Load the input file (Palestinian districts and their town with population).\n");
    printf("2. Print the loaded information before sorting (as in the input file format)\n");
    printf("3. Sort the districts alphabetically using Radix sort.\n");
    printf("4. Sort the towns for each district based on population in ascending order\n");
    printf("5. Print the sorted information.\n");
    printf("6. Add a new district to the list of sorted districts (and sort the list)\n");
    printf("7. Add a new town to a certain district.\n");
    printf("8. Delete a town from a specific district\n");
    printf("9. Delete a complete district; here, you must delete all towns belonging to that district before deleting it.\n");
    printf("10.Calculate the population of Palestine, the max and min town population\n");
    printf("11.Print the districts and their total population (without towns details). \n");
    printf("12.Change the population of a town, after prompting the user to enter the district name. \n");
    printf("13.Save to output file.\n");
    printf("14.Exit\n\n");
}

void insertDistrict_new(district d, char *name, char *c1, int c2)
{
    district temp;
    temp = d;
    while (temp->nextdistrict != NULL)
    {
        temp = temp->nextdistrict;
        if (strcmp(temp->d, name) == 0)
        {
            printf("the district already exist\n");
            return;
        }
    }
    district p = makeEmpty(NULL);
    p->nextdistrict = d->nextdistrict;
    if (d->nextdistrict != NULL)
        d->nextdistrict->prev = p;
    d->nextdistrict = p;
    p->prev = d;
    if (c1 != '\0')
    {
        town t = makeEmpty_Town(NULL);
        p->next = t;
        t->prevDistrict = p;
        strncpy(p->d, name, sizeof(p->d));
        strncpy(t->t, c1, sizeof(t->t));
        t->popTown = c2;
    }
    else
        p->next = NULL;
    strncpy(p->d, name, sizeof(p->d));
}

void cutLine(char *s, district d)
{
    char *c, *c1, *c2;
    // to cut the line : district | town | population
    c = strtok(s, "|");
    c1 = strtok(NULL, "|");
    c2 = strtok(NULL, "");
    printf("%s %s\n",c,c1);
    int res = atoi(c2);
    district temp;
    temp = d;
    if (d == NULL)
    {
        printf("there is no list\n");
    }
    // search for the district then insert the town if its exist
    while (temp->nextdistrict != NULL)
    {
        temp = temp->nextdistrict;
        if (strcmp(temp->d, c) == 0)
        {
            insertTown(temp, c1, res);
            return;
        }
    }
    // insert a new district from file
    insertDistrict_new(d, c, c1, res);
}

void insertTown(district temp, char *c1, int c2)
{
    town ptr;
    ptr = temp->next;
    district l;
    l = temp;
    while (ptr != NULL)
    {
        if (strcmp(ptr->t, c1) == 0)
        {
            printf("this town %s already in district %s\n\n", c1, temp->d);
            return;
        }
        ptr = ptr->nextT;
    }
    town t = makeEmpty_Town(NULL);
    if (l->next != NULL)
    {
        t->nextT = l->next;
        t->prevDistrict = temp;
        t->prevT = NULL;
        temp->next->prevT = t;
        temp->next = t;
    }
    else
    {
        temp->next = t;
        t->prevDistrict = temp;
    }
    strncpy(t->t, c1, sizeof(t->t));
    t->popTown = c2;
}

void printListBeforeSort(district l)
{
    district p;
    p = l;
    while (p->nextdistrict != NULL)
    {
        p = p->nextdistrict;
    }
    while (p != l)
    {
        printTown(p);
        p = p->prev;
    }
}

void printTown(district l)
{
    town i;
    i = l->next;
    if (i == NULL)
    {
        printf("%s|null|0\n", l->d);
        return;
    }
    while (i->nextT != NULL)
    {
        if (i->nextT == NULL)
        {
            break;
        }
        i = i->nextT;
    }
    while (i != NULL)
    {
        printf("%s|%s|%d\n", l->d, i->t, i->popTown);
        i = i->prevT;
    }
}

void insertDistrict(district d, char *name)
{
    district temp = makeEmpty(NULL);
    temp->nextdistrict = d->nextdistrict;
    if (d->nextdistrict != NULL)
        d->nextdistrict->prev = temp;
    temp->prev = d;
    d->nextdistrict = temp;
    strncpy(temp->d, name, sizeof(temp->d));
}

void sortTown(district l)
{
    town i;
    town j;
    i = l->next;
    if (i == NULL)
        return;
    while (i->nextT != NULL)
    {
        j = i->nextT;
        while (j != NULL)
        {
            if (i->popTown < j->popTown)
            {
                town t = makeEmpty_Town(NULL);
                t->popTown = i->popTown;
                strncpy(t->t, i->t, sizeof(t->t));
                i->popTown = j->popTown;
                strncpy(i->t, j->t, sizeof(i->t));
                j->popTown = t->popTown;
                strncpy(j->t, t->t, sizeof(j->t));
            }
            j = j->nextT;
        }
        i = i->nextT;
    }
}

void sortDistrict(district l)
{
    size_t maxLen = 0;
    int size = getSize(l);
    district temp;
    temp = l->nextdistrict;
    // get the max length of district
    while (temp != NULL)
    {
        if (strlen(temp->d) > maxLen)
            maxLen = strlen(temp->d);
        temp = temp->nextdistrict;
    }
    district sort[28];
    district s[28];
    for (int i = 0; i < 28; i++)
    {
        sort[i] = makeEmpty(NULL);
        s[i] = sort[i];
    }
    for (int i = maxLen - 1; i >= 0; i--)
    {
        temp = l->nextdistrict;
        while (temp != NULL)
        {
            if (temp->d[i] == '\0')
            {
                s[0]->nextdistrict = temp;
                s[0] = s[0]->nextdistrict;
                temp = temp->nextdistrict;
                s[0]->nextdistrict = NULL;
                continue;
            }
            int index = temp->d[i] - ('a' - 1);
            // for small latter
            if (index > 0 && index < 27)
            {
                s[index]->nextdistrict = temp;
                s[index] = s[index]->nextdistrict;
                temp = temp->nextdistrict;
                s[index]->nextdistrict = NULL;
            }
            // for the capital latter
            else if (index < 0 && index > -32)
            {
                s[index + 32]->nextdistrict = temp;
                temp->prev = s[index + 32];
                s[index + 32] = s[index + 32]->nextdistrict;
                temp = temp->nextdistrict;
                s[index + 32]->nextdistrict = NULL;
            }
            // for anything else
            else
            {
                s[27]->nextdistrict = temp;
                temp->prev = s[27];
                s[27] = s[27]->nextdistrict;
                temp = temp->nextdistrict;
                s[27]->nextdistrict = NULL;
            }
        }
        l->nextdistrict = NULL;
        temp = l;
        int count = 0;
        int x = 0;
        for (int j = 0; j < 28; j++)
            s[j] = sort[j]->nextdistrict;
        while (count < size)
        {
            while (s[x] != NULL)
            {
                temp->nextdistrict = s[x];
                if (temp->nextdistrict != NULL)
                    temp->nextdistrict->prev = temp;
                temp = temp->nextdistrict;
                s[x] = s[x]->nextdistrict;
                temp->nextdistrict = NULL;
                count++;
            }
            x++;
        }
        for (int y = 0; y < 28; y++)
        {
            sort[y] = makeEmpty(NULL);
            s[y] = sort[y];
        }
    }
}

void printAfterSorting(district l)
{
    district temp;
    temp = l->nextdistrict;
    while (temp != NULL)
    {
        // print the town of district
        printTown(temp);
        temp = temp->nextdistrict;
    }
}

int getSize(district l)
{
    district temp;
    int n = 0;
    temp = l->nextdistrict;
    while (temp != NULL)
    {
        n++;
        temp = temp->nextdistrict;
    }
    return n;
}
