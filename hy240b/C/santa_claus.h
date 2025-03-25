/**********************************************************************
 * @file   santa_claus.h                                              *
 * @author Papaioannou Antonis <papaioan@csd.uoc.gr>                  *
 *                                                                    *
 * @brief  Header file with the structures and function prototypes    *
 * for the needs of the Data Structures (HY-240a) project (Fall 2015) *
 * Computer Science Department, University of Crete, Greece           *
**********************************************************************/
 
#define M 3 /*Number of child's preferences*/
#define N 4 /*Number of children's age categories*/
 
int primes_g[669] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
        71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139,
        149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223,
        227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
        307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383,
        389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
        467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569,
        571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647,
        653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743,
        751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839,
        853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
        947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, 1031,
        1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097, 1103,
        1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201,
        1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289,
        1291, 1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381,
        1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471,
        1481, 1483, 1487, 1489, 1493, 1499, 1511, 1523, 1531, 1543, 1549, 1553,
        1559, 1567, 1571, 1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619, 1621,
        1627, 1637, 1657, 1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723,
        1733, 1741, 1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811, 1823,
        1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889, 1901, 1907, 1913,
        1931, 1933, 1949, 1951, 1973, 1979, 1987, 1993, 1997, 1999, 2003, 2011,
        2017, 2027, 2029, 2039, 2053, 2063, 2069, 2081, 2083, 2087, 2089, 2099,
        2111, 2113, 2129, 2131, 2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207,
        2213, 2221, 2237, 2239, 2243, 2251, 2267, 2269, 2273, 2281, 2287, 2293,
        2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357, 2371, 2377, 2381,
        2383, 2389, 2393, 2399, 2411, 2417, 2423, 2437, 2441, 2447, 2459, 2467,
        2473, 2477, 2503, 2521, 2531, 2539, 2543, 2549, 2551, 2557, 2579, 2591,
        2593, 2609, 2617, 2621, 2633, 2647, 2657, 2659, 2663, 2671, 2677, 2683,
        2687, 2689, 2693, 2699, 2707, 2711, 2713, 2719, 2729, 2731, 2741, 2749,
        2753, 2767, 2777, 2789, 2791, 2797, 2801, 2803, 2819, 2833, 2837, 2843,
        2851, 2857, 2861, 2879, 2887, 2897, 2903, 2909, 2917, 2927, 2939, 2953,
        2957, 2963, 2969, 2971, 2999, 3001, 3011, 3019, 3023, 3037, 3041, 3049,
        3061, 3067, 3079, 3083, 3089, 3109, 3119, 3121, 3137, 3163, 3167, 3169,
        3181, 3187, 3191, 3203, 3209, 3217, 3221, 3229, 3251, 3253, 3257, 3259,
        3271, 3299, 3301, 3307, 3313, 3319, 3323, 3329, 3331, 3343, 3347, 3359,
        3361, 3371, 3373, 3389, 3391, 3407, 3413, 3433, 3449, 3457, 3461, 3463,
        3467, 3469, 3491, 3499, 3511, 3517, 3527, 3529, 3533, 3539, 3541, 3547,
        3557, 3559, 3571, 3581, 3583, 3593, 3607, 3613, 3617, 3623, 3631, 3637,
        3643, 3659, 3671, 3673, 3677, 3691, 3697, 3701, 3709, 3719, 3727, 3733,
        3739, 3761, 3767, 3769, 3779, 3793, 3797, 3803, 3821, 3823, 3833, 3847,
        3851, 3853, 3863, 3877, 3881, 3889, 3907, 3911, 3917, 3919, 3923, 3929,
        3931, 3943, 3947, 3967, 3989, 4001, 4003, 4007, 4013, 4019, 4021, 4027,
        4049, 4051, 4057, 4073, 4079, 4091, 4093, 4099, 4111, 4127, 4129, 4133,
        4139, 4153, 4157, 4159, 4177, 4201, 4211, 4217, 4219, 4229, 4231, 4241,
        4243, 4253, 4259, 4261, 4271, 4273, 4283, 4289, 4297, 4327, 4337, 4339,
        4349, 4357, 4363, 4373, 4391, 4397, 4409, 4421, 4423, 4441, 4447, 4451,
        4457, 4463, 4481, 4483, 4493, 4507, 4513, 4517, 4519, 4523, 4547, 4549,
        4561, 4567, 4583, 4591, 4597, 4603, 4621, 4637, 4639, 4643, 4649, 4651,
        4657, 4663, 4673, 4679, 4691, 4703, 4721, 4723, 4729, 4733, 4751, 4759,
        4783, 4787, 4789, 4793, 4799, 4801, 4813, 4817, 4831, 4861, 4871, 4877,
        4889, 4903, 4909, 4919, 4931, 4933, 4937, 4943, 4951, 4957, 4967, 4969,
        4973, 4987, 4993, 4999
};
 
/*Needed structs definition*/
 
/*Structure defining a node of the children tree*/
struct child {
    int cid; /*The identifier of the child.*/
    int age; /*The age of the child.*/
    int did; /*The identifier of the child.*/
    int present_choices[M]; /*The array in which the preferences of the child for presents are stored*/
    struct child *lc; /* left child */
    struct child *rc; /* right child */
};
 
/*Structure defining a node of the presents tree*/
struct present {
    int pid; /*The identifier of the present*/
    int stock_cnt; /*The counter of available presents in stock*/
    int request_cnt; /*The counter of requested presents in stock*/
    struct present *parent; /* parent node */
    struct present *lc; /* left child */
    struct present *rc; /* right child */
};
 
/*Structure defining a record of the present assignments (used in present assignments hash table) */
struct present_assign {
    int cid; /*The identifier of the child that the present assigned to*/
    int pid; /*The identifier of the present assigned to the child*/
    int s_degree; /*The degree of satisfaction of the child who received the present*/
};
 
/*Structure defining a node of the districts list*/
struct district {
    int did; /*The identifier of the district that the child lives in*/
    int children_cnt; /* no. of children live in this district */
    struct present_assign *assignHT; /* the hash table of present assignments of this district*/
    struct district *next; /* Singly-linked list */
};
 
extern struct child *Age_categories[N]; /*The array of the children's age categories*/
 
extern struct present *stock_tree; /* global variable pointing to the root of the stock tree */
extern struct present *stock_sentinel; /* global variable pointing to the sentinel node of the stock tree */
 
/*Needed function protypes definition*/
 
/**
 * @brief Create a new present and add it to the stock
 *
 * @param pid The new present's id
 * @param stock_cnt The instances of the new present to be stored at the stock
 *
 * @return 1 on success
 *         0 on failure
 */
int buy_present(int pid, int stock_cnt);
//void insert_present(int pid,int stock_cnt);
struct present* insert_present( struct present *p, int pid, int stock_cnt );
//void insert_present( struct present **p,struct present *prev,int pid,int stock_cnt);
//struct present* print_inorder(struct present *p,struct present*prev,int pid,int stock_cnt);
//void inorder(struct present *p);
//void inorder(struct present *p,int pid,int stock_cnt);
//struct present* inorder(struct present *p,int pid,int stock_cnt);
//int inorder(struct present *p,int pid,int stock_cnt);
//void visit(struct present *p);
void print_inorder(struct present * p);
//int  print_inorder(struct present * p);
//void inorderrec(struct present *p,struct present *prev,int pid1,int pid2,int pid3);
struct present* inorderrec(struct present *p,struct present *prev,int pid1,int pid2,int pid3);
/**
 * @brief Create a new request for present from the child  and handle the counters about the stock
 *
 * @param cid The id of the child who sent the letter
 * @param age The age of the child
 * @param did The id of the district in which the child lives
 * @param pid1 The id of the present of the 1st preference of the child
 * @param pid2 The id of the present of the 2nd preference of the child
 * @param pid3 The id of the present of the 3rd preference of the child
 *
 * @return 1 on success
 *         0 on failure
 */
int letter_received(int cid, int age, int did, int pid1, int pid2, int pid3);
//void insert_child(struct child *c, int age_cat);
struct child* insert_child(struct child *c, int age_cat);
 void preorder(struct child *c,int age_cat);
struct child *findLeftmostNode(struct child*c);
struct child* nextInorderSuccessor(struct child* root, struct child* find);
struct child *findnextsmallest(struct child*c,int age_cat);
 
/**
 * @brief Assign presents to children taking into consideration their preference and stock availability
 *
 * @return 1 on success
 *         0 on failure
 */
int prepare_presents(void);
 
/**
 * @brief Assign a satisfaction degree to the present received by the child
 *
 * @param cid The id of the child who gives feedback
 * @param did The id of the district where the child lives
 * @param s_degree The number of the satisfaction degree of the child
 *
 * @return 1 on success
 *         0 on failure
 */
int give_feedback(int cid, int did, int s_degree);
 
/**
 * @brief Sort the stock list of presents
 *
 * @return 1 on success
 *         0 on failure
 */
int analytics(int k);
 
/**
 * @brief Change the year of presents dispatch
 *
 * @return 1 on success
 *         0 on failure
 */
int new_season(void);
 
/**
 * @brief Remove children who did not send a letter to Santa Claus
 *
 * @return 1 on success
 *         0 on failure
 */
int clear_list_of_children(void);
 struct child* remove_child(struct child *c, int age_cat);
/**
 * @brief Search for a specific present in stock list of presents
 *
 * @param pid The id of the present searched
 *
 * @return 1 on success
 *         0 on failure
 */
int search_present(int pid);
 void searchprint_inorder(struct present *p,int pid);
/**
 * @brief Print the children lists of all age categories
 *
 * @return 1 on success
 *         0 on failure
 */
int print_child(void);
 
/**
 * @brief Print the children id and presents id of all districts
 *
 * @return 1 on success
 *         0 on failure
 */
int print_district(void);
 
/**
 * @brief Print the id of available presents of the stock
 *
 * @return 1 on success
 *         0 on failure
 */
int print_stock(void);
void print_inorder_adiatheto(struct present *p);