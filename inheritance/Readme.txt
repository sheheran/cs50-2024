Each of a child's parents randomly passes one of their two blood type alleles to their children.
The possible blood type combinations are
OO  OA  OB  AO  AA  AB  BO  BA  BB

Example -

Parent 01 - AO and Parent 02 - BB
Child - AB OB


Parent 01 - AO and Parent 02 - OB
Child - AO OB AB OO


Complete the implementation of inheritance.c,
such that it creates a family of a specified generation size and assigns blood type alleles to each family member.
The oldest generation will have alleles assigned randomly to them.

The "create_family" function takes an integer (generations) as input and via "malloc" one "person" for each member of the family of that generations,
Returning a pointer to the "person" in the youngest generation.

typedef struct person
{
	struct person *parents[2]; //every person having an array of twp parents, each of the parents is a pointer to another person,
	char alleles[2]; //representing two alleles (A, B, O)
}
person;

Example

-	"create_family(3)" should return a pointer to a 1(person) with 2(two parents), where each 3(parent also has two parents).

// Create a new family with three generations
person *p = create_family(GENERATIONS);
// To create a family with a specified number of generations, returning a pointer to the most recent generation, of 'person' in thatr family.
// If we create a family of three generations, it will return a pointer to one person, but through that person's pointers,
// We could find out that persons parents as well-as grand parents.

-	Each 'person' should have 'alleles' assigned to them. The oldest generation should have alleles randomly chosen (by calling the 'random_allele' function),
	and younger generation should inherit one allele chosen at random from each parent.

-	Each 'person' should have parents assigned to them. The oldest generation should have both parents set to NULL, and younger generations have 'parents' be an array of two pointers,
	each pointing to a different parent.

// Free memory, that allocated in the process of creating the family
free_family(p);




Complete the "create_family" function to create a family with a specified number of generations.
-	Allocate memory with malloc for a new person.
-	If "generations > 1" recursively create previous generations.
-	Update the new person's parents.
-	Inherit alleles from parents.
If generation == 1, no previous generations
-	Set parents to NULL
-	Randomly generate alleles

Complete the free_family function to free all allocated memory
-	Baase case: Handle input of NULL (If the input to free_family is null there is no action to be taken)
-	Recursive case: recursively free parents, then free the child

