/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet  2                                          */
/*                                                                          */ 
/****************************************************************************/

/****************************************************************************/
/*                                                                          */ 
/* File Name : library2.h                                                   */ 
/*                                                                          */ 
/****************************************************************************/

#ifndef _234218_WET2_
#define _234218_WET2_


#ifdef __cplusplus
extern "C" {
#endif




/* Return Values
 * ----------------------------------- */
typedef enum {
	SUCCESS = 0,
	FAILURE = -1,
	ALLOCATION_ERROR = -2,
	INVALID_INPUT = -3

} StatusType;



/* Required Interface for the Data Structure
 * -----------------------------------------*/



/* Description:   Initializes F.I.E.L.D with n teams.
 * Input:         n - Number of teams.
 * Output:        None.
 * Return Values: A pointer to a new instance of the data structure - as a void* pointer.
 */
void*       Init(int n);


/* Description:   A super hero was added to the system.
 * Input:         DS - A pointer to the data structure.
 *                superheroID - The ID of the super hero.
 *                strength - initial strength value of the super hero.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or superheroID<0 or strength<0.
 *                FAILURE - If a super hero with superheroID already in the system, or in the case of any other problem.
 *                SUCCESS - Otherwise.
 */
StatusType   AddSuperhero(void* DS, int superheroID, int strength);


/* Description:   The super hero with ID superheroID decides to join a team.
 * Input:         DS - A pointer to the data structure.
 *                superheroID - The ID of the super hero.
 *                team - The ID of the team he joins.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, superheroID<0 or team is not an illegal team number.
 *                FAILURE - If a super hero with same ID already assigned to another team, there is no super hero in the system with this ID or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType   AssignSuperhero(void* DS, int superheroID, int team);


/* Description:   Joins the two departments of team1 and team2 together, the name of the joined departments is the name of team1 department.
 * Input:         DS - A pointer to the data structure.
 *                team1 - The identifier of the 1st team.
 *                team2 - The identifier of the 2nd team.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or either team1 or team2 are illegal team numbers.
 *                FAILURE - If both teams belong to the same departments, or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType   JoinDepartments(void* DS, int team1, int team2);


/* Description:   Returns the department to which superheroID belongs.
 * Input:         DS - A pointer to the data structure.
 *                superheroID - The identifier of the super hero.
 * Output:        department - The identifier of the department.
 * Return Values: INVALID_INPUT - If DS==NULL, superheroID<0 or department==NULL.
 *                FAILURE - If there is no super hero in the system with this ID, or superheroID doesn't belong to any team or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType   GetDepartment(void* DS, int superheroID, int* department);


/* Description:   Multiplies the strength of every super hero in teamID in factor.
 * Input:         DS - A pointer to the data structure.
 *                teamID - The team which is upgraded.
 *                factor - the factor in which to multiply the strength of the super heros.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 * 				  INVALID_INPUT - If DS==NULL, factor<1 or teamID is an illegal team number.
 *                SUCCESS - Otherwise.
 */
StatusType   TeamUpgrade(void* DS, int teamID, int factor);

/* Description:   Returns the ID of the strongest super hero in department depID.
 * 				  If two or more super heros have the same strength, the super hero with minimal ID is returned.
 * Input:         DS - A pointer to the data structure.
 *                depID - The identifier of the department.
 * Output:        superhero - The identifier of the super hero.
 * Return Values: INVALID_INPUT - If DS==NULL, depID isn't in range 0,.., n-1 or superhero==NULL.
 *                FAILURE - If there is no super heros in depID or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType   GetStrongestSuperhero(void* DS, int depID, int* superhero);

/* Description:   Returns the number of super heros in system with strength in range (min, max].
 * Input:         DS - A pointer to the data structure.
 *                min - The strength minimal value.
 *                max - The strength maximal value.
 * Output:        num - The number of super heros.
 * Return Values: INVALID_INPUT - If DS==NULL, num==NULL, min>=max or min<0.
 *                FAILURE - In case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType   GetNumOfSuperherosInRange(void* DS, int min, int max, int* num);

/* Description:   Quits and deletes the database.
 *                The variable pointed by DS should be set to NULL.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */
void        Quit(void** DS);





#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET2_ */ 

