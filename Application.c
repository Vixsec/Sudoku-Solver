

#include <stdio.h>
#include <stdlib.h>

int  boardInputVerification( int* board );  /*  Validate user input board          */
void solveBoard( int *board );              /*  Solve for every possible solution  */
void renderBoard( int* board );             /*  Render a "formated" sudoku board   */

int canPlace( int *board, const int value, const int row, const int col );      /*  Compares all check_function results & returns 1 if current value fits     */
int checkRowCol( int *board, const int value, const int row, const int col );   /*  Checks row & column for current value, returns 1 if current value fits  */
int check3X3Block( int *board, const int value, const int row, const int col ); /*  Checks a 3x3 grid for current value, returns 1 if current value fits        */



void main( )
{
    
    int* board = calloc( 82, sizeof( int ) );
    printf("[?] Enter board:\n[+] ");

    if( boardInputVerification( board ) )
    {
        solveBoard( board );
    }
    
    return;
}



int boardInputVerification( int *board )
{
    register int ch = getchar();
    int index = 0;

    for( ; ( ch >47 && ch <58 ) ; ch=getchar( ) )
    {
        board[ index ] = ch -48;
        ++index;
    }

    if( index != 81 )
    {
        printf( "\n[!] INPUT ERROR: Board<SUDOKU> invalid!\n[!] ERROR non-int @ index( %d )!", index );
        return 0;
    }
    return 1;
}



void solveBoard( int *board )
{
    for( int row=0 ; row<9 ; ++row )
    {
        for( int col=0 ; col<9 ; ++col )
        {
            if( board[ row *9 +col ] == 0 )
            {
                for( int val=1 ; val<10 ; ++val )
                {
                    if( canPlace( board, val, row, col ) )
                    {
                        board[ row *9 +col ] = val;
                        solveBoard( board );
                        board[ row *9 +col ] = 0;
                    }
                }
                return;
            }
        }
    }
    renderBoard( board );
    printf( "\nMORE POSSABLE SOLUTIONS?! <ENTER>" );
    getchar( );
    return;
}



void renderBoard( int *board )
{
    printf( "\n" );
    for( int row=0 ; row<9 ; ++row )
    {
        if( row%3 == 0 && row != 0 )
        {
            printf( "------+-------+------\n" );
        }
        for( int col=0 ; col<9 ; ++col )
        {
            if( col != 0 && col %3 == 0 )
            {
                printf( "| " );
            }
            printf( "%d ", board[ row * 9 + col ] );
        }
        printf( "\n" );
    }
}



int canPlace( int *board, const int value, const int row, const int col )
{
    if( checkRowCol( board, value, row, col ) && check3X3Block( board, value, row, col ) )
    {
        return 1;
    }
    return 0;
}



int checkRowCol( int *board, const int value, const int row, const int col )
{
    for( int offset=0 ; offset<9 ; ++offset )
    {
        if( board[ offset *9 +col ] == value || board[ row *9 +offset ] == value )
        { 
            return 0;
        }
    }
    return 1;
}



int check3X3Block( int *board, const int value, const int row, const int col )
{
    int X_LOC = ( row/3 ) *3;
    int Y_LOC = ( col/3 ) *3;

    for( int rInc=0 ; rInc<3 ; ++rInc )
    {
        for( int cInc=0 ; cInc<3 ; ++cInc )
        {
            if( board[ ( (X_LOC +rInc) *9 ) +( Y_LOC +cInc ) ] == value )
            {
                return 0;
            }
        }
    }
    return 1;
}
