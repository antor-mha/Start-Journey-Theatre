#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the movie struct
struct Movie
{
    char title[50];
    char director[50];
    int year;
    float rating;
};

// Define the reservation struct
struct Reservation
{
    char movie_title[50];
    int seat_number;
};

// Function prototypes
void admin_panel();
void viewer_panel();
int check_password();
void add_movie();
void delete_movie();
void view_movies();
void view_revenue();
void search_movie();
void reserve_seat();
void cancel_reservation();
void view_reservations();

// Define global variables
int num_movies = 0;
int num_reservations = 0;
struct Movie movies[50];
struct Reservation reservations[100];

// main execution area

int main()
{
    int choice;
    title();

    while (1)
    {
        printf("Select an option:\n");
        printf("1. Admin Panel\n");
        printf("2. Viewer Panel\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            admin_panel();
            break;
        case 2:
            viewer_panel();
            break;
        case 3:
            printf("------------------------------------------------------\n");
            printf("Thank you for using the Start Journey Theatre program.\n");
            printf("------------------------------------------------------\n");
            return 0;
        default:
            printf("---------------------------------------\n");
            printf("Invalid choice. Please try again later.\n");
            printf("---------------------------------------\n");
        }
    }
}
// End of main execution area

//Start of title function
void title() {
    printf("\n\n\n\n\n\n\n\t\t\t\t::::::::::::::::::::==================::::::::::::::::::::");
    printf("\n\t\t\t\t::\t\t\tWELCOME TO\t\t\t::");
    printf("\n\t\t\t\t::\t\t The Start Journey Theatre \t\t::");
    printf("\n\t\t\t\t::::::::::::::::::::==================::::::::::::::::::::\n\n");
}
//End of title function

// Start of admin panel function
void admin_panel()
{
    int password = check_password();
    int choice;

    if (password)
    {
        while (1)
        {
            printf("------------\n");
            printf("Admin Panel:\n");
            printf("------------\n");
            printf("Select an option:\n");
            printf("1. Add Movie\n");
            printf("2. Delete Movie\n");
            printf("3. View Movies\n");
            printf("4. View Revenue\n");
            printf("5. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            printf("\n");

            switch (choice)
            {
            case 1:
                add_movie();
                break;
            case 2:
                delete_movie();
                break;
            case 3:
                view_movies();
                break;
            case 4:
                view_revenue();
                break;
            case 5:
                printf("Existing Admin Panel.\n");
                return;
            default:
                printf("---------------------------------------\n");
                printf("Invalid choice. Please try again later.\n");
                printf("---------------------------------------\n");
            }
        }
    }
    else
    {
        printf("Access Denied.\n");
    }
}
// End of admin panel function

// Start of viewer panel function
void viewer_panel()
{
    int choice;

    while (1)
    {
        printf("-------------\n");
        printf("Viewer Panel:\n");
        printf("-------------\n");
        printf("Select an option:\n");
        printf("1. View All Movies\n");
        printf("2. Search Movie\n");
        printf("3. Reserve a Seat\n");
        printf("4. Cancel Reservation\n");
        printf("5. Display All Reservations\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            view_movies();
            break;
        case 2:
            search_movie();
            break;
        case 3:
            reserve_seat();
            break;
        case 4:
            cancel_reservation();
            break;
        case 5:
            view_reservations();
            break;
        case 6:
            return;
        default:
            printf("---------------------------------------\n");
            printf("Invalid choice. Please try again later.\n");
            printf("---------------------------------------\n");
        }
    }
}
// End of viewer panel function

// Function to add a movie
void add_movie()
{
    struct Movie movie;

    printf("Enter the details of the movie:\n");
    printf("Title: ");
    scanf("%s", movie.title);
    printf("Director: ");
    scanf("%s", movie.director);
    printf("Year: ");
    scanf("%d", &movie.year);
    printf("Rating: ");
    scanf("%f", &movie.rating);
    printf("\n");

    FILE *fp = fopen("movies.txt", "a");
    fprintf(fp, "%s,%s,%d,%.1f\n", movie.title, movie.director, movie.year, movie.rating);
    fclose(fp);

    movies[num_movies++] = movie;

    printf("Movie added successfully.\n\n");
}
// End of add movie function

// Function to delete a movie
void delete_movie()
{
    char title[50];
    int found = 0;

    printf("Enter the title of the movie to delete: ");
    scanf("%s", title);
    printf("\n");

    FILE *fp = fopen("movies.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    char buffer[200];

    while (fgets(buffer, 200, fp))
    {
        char *ptr = strtok(buffer, ",");
        if (strcmp(ptr, title) != 0)
        {
            fprintf(temp, "%s", buffer);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("movies.txt");
    rename("temp.txt", "movies.txt");

    if (found)
    {
        printf("Movie deleted successfully.\n\n");
    }
    else
    {
        printf("Movie not found.\n\n");
    }
}
// End of the delete movie function

// Function to search for a movie
void search_movie()
{
    char title[50];
    int found = 0;

    printf("Enter the title of the movie to search: ");
    scanf("%s", title);
    printf("\n");

    FILE *fp = fopen("movies.txt", "r");

    char buffer[200];

    while (fgets(buffer, 200, fp))
    {
        char *ptr = strtok(buffer, ",");
        if (strcmp(ptr, title) == 0)
        {
            printf("Title: %s", ptr);
            printf("Director: %s", strtok(NULL, ","));
            printf("Year: %s", strtok(NULL, ","));
            printf("Rating: %s\n\n", strtok(NULL, ","));
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
    {
        printf("Movie not found.\n\n");
    }
}
// End of search movie function

// Function to view the list of movies
void view_movies()
{
    FILE *fp = fopen("movies.txt", "r");

    printf("----------------\n");
    printf("Available Shows:\n");
    printf("----------------\n");

    char buffer[200];

    while (fgets(buffer, 200, fp))
    {
        printf("%s", buffer);
    }

    fclose(fp);
    printf("\n");
}
// End of view movies function

// Function to view all reservations
void view_reservations()
{
    FILE *fp = fopen("reservations.txt", "r");

    char buffer[200];
    char *ptr;

    printf("\n");

    while (fgets(buffer, 200, fp))
    {
        ptr = strtok(buffer, ",");
        printf("Title: %s", ptr);
        printf("Reserved Seats: %s\n\n", strtok(NULL, ","));
    }

    fclose(fp);
}
// End of view reservations function

// Function to reserve a seat
void reserve_seat()
{
    char title[50];
    int seats;
    int found = 0;

    printf("Enter the title of the movie to reserve a seat: ");
    scanf("%s", title);
    printf("\nEnter the number of seats to reserve: ");
    scanf("%d", &seats);

    FILE *fp = fopen("reservation.txt", "a+");

    char buffer[200];
    char *ptr;

    while (fgets(buffer, 200, fp))
    {
        ptr = strtok(buffer, ",");
        if (strcmp(ptr, title) == 0)
        {
            ptr = strtok(NULL, ",");
            int available_seats = atoi(ptr);
            if (available_seats >= seats)
            {
                fseek(fp, -strlen(buffer), SEEK_CUR);
                int new_seats = available_seats - seats;
                sprintf(buffer, "%s,%d\n", title, new_seats);
                fputs(buffer, fp);
                printf("\n%d Seats reserved for %s.\n\n", seats, title);
            }
            else
            {
                printf("\n%d Seats are not available for %s.\n\n", seats, title);
            }
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nMovie not found.\n\n");
    }

    fclose(fp);
}
// End of reserve seat function

// Function to cancel a reservation
void cancel_reservation()
{
    char title[50];
    int seats;
    int found = 0;

    printf("Enter the title of the movie to cancel a reservation: ");
    scanf("%s", title);
    printf("\nEnter the number of seats to cancel: ");
    scanf("%d", &seats);

    FILE *fp = fopen("reservations.txt", "a+");

    char buffer[200];
    char *ptr;

    while (fgets(buffer, 200, fp))
    {
        ptr = strtok(buffer, ",");
        if (strcmp(ptr, title) == 0)
        {
            ptr = strtok(NULL, ",");
            int available_seats = atoi(ptr);
            fseek(fp, -strlen(buffer), SEEK_CUR);
            int new_seats = available_seats + seats;
            sprintf(buffer, "%s,%d\n", title, new_seats);
            fputs(buffer, fp);
            printf("\n%d seats canceled for %s.\n\n", seats, title);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nMovie not found.\n\n");
    }

    fclose(fp);
}
// End of cancel reservation function

// Function to check the password
int check_password()
{
    char password[50];

    printf("Enter the admin password: ");
    scanf("%s", password);
    printf("\n");

    if (strcmp(password, "admin123") == 0)
    {
        printf("Access Granted. You may proceed now.\n\n");
        return 1;
    }
    else
    {
        printf("Access Denied.\n\n");
        return 0;
    }
}
// End of check password function

// Function to view the revenue
void view_revenue()
{
    float revenue = num_reservations * 10.0;

    printf("Total Revenue: $%.2f\n\n", revenue);
}
// End of view revenue function
