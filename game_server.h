#ifndef GAME_SERVER_H
#define GAME_SERVER_H
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <signal.h>
#include <sys/time.h>


#ifndef PORT
  #define PORT 8888
#endif


#define NAME 0		//reflects 2 states of client connection: 0 - identification, 1 - identified, can enter commands
#define COMMAND 1

#define DELIM " \n"

#define TIMER_TICK 120
#define MAX_NAME 10     // Max playername length
#define INPUT_ARG_MAX_NUM 10

#define BUFFER_SIZE 1024

//Node for the linked list which stores currently connected clients
typedef struct client {
    int fd;
    int state; // either NAME or COMMAND
    char name[MAX_NAME];
    char buf[BUFFER_SIZE];  // each client has its own buffer
    int inbuf;              // and a personal pointer to the current place in buffer
    struct client *next;
} Client;

//Node for linked list which stores all players ever played - these are never removed
typedef struct player {
    char name[MAX_NAME]; 
    int max_score;
    int total_games;
    int total_score; 
    struct player *next;
} Player;


//=====================================
// These are implemented in players.c
//=====================================

/*
 * Create a new player with the given name.  Insert it at the tail of the list
 * of players whose head is pointed to by *player_ptr_add.
 *
 * Return:
 *   - 0 if successful
 *   - 1 if a player by this name already exists in this list
 *   - 2 if the given name cannot fit in the 'name' array 
 *   - in this case truncate the name (don't forget about the null terminator), 
 *		add to the list, and return 2 to send message to the client that name was truncated.
 *       
 */
int create_player(const char *name, Player **player_ptr_add);


/*
 * Return a pointer to the player with this name in
 * the list starting with head. Return NULL if no such player exists.
 *
 * NOTE: You'll likely need to cast a (const Player *) to a (Player *)
 * to satisfy the prototype without warnings.
 */
Player *find_player(const char *name, const Player *head);


//=====================================
// These implemented in game_server.c
//=====================================

/*
 * Sets up server socket: bind and listen
 * Returns a file descriptor for listening and accepting new connections
 */
int setup (void);

void timer_handler(int sig);

/* accept new connection and calls add_client */
void new_connection(int listenfd) ;

/* Sets up Client fields, add to the list, and ask for the name */
void add_client(int fd, struct in_addr addr);
/* remove client from the list */
void remove_client(int fd);

void sendclient(Client *p, char *msg);
void receiveclient(Client *p);


void interpret_message(Client *p);

int parse_line(Client *p);
int do_command(struct client * p, int cmd_argc, char **cmd_argv);

int find_network_newline(char *buf, int inbuf);

#endif