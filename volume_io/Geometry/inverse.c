
#ifndef lint
static char rcsid[] = "$Header: /private-cvsroot/minc/volume_io/Geometry/inverse.c,v 1.5 1995-02-20 13:12:07 david Exp $";
#endif

#include  <internal_volume_io.h>

/* ----------------------------- MNI Header -----------------------------------
@NAME       : compute_transform_inverse
@INPUT      : transform
@OUTPUT     : inverse
@RETURNS    : TRUE if successful
@DESCRIPTION: Computes the inverse of the given transformation matrix.
@METHOD     : 
@GLOBALS    : 
@CALLS      : 
@CREATED    : 1993            David MacDonald
@MODIFIED   : 
---------------------------------------------------------------------------- */

public  BOOLEAN   compute_transform_inverse(
    Transform  *transform,
    Transform  *inverse )
{
    int        i, j;
    Real       **t, **inv;
    Transform  ident;
    BOOLEAN    success;

    /* --- copy the transform to a numerical recipes type matrix */

    ALLOC2D( t, 4, 4 );
    ALLOC2D( inv, 4, 4 );

    for_less( i, 0, 4 )
    {
        for_less( j, 0, 4 )
        {
            t[i][j] = Transform_elem(*transform,i,j);
        }
    }

    success = invert_square_matrix( 4, t, inv );

    if( success )
    {
        /* --- copy the resulting numerical recipes matrix to the
               output argument */

        for_less( i, 0, 4 )
        {
            for_less( j, 0, 4 )
            {
                Transform_elem(*inverse,i,j) = inv[i][j];
            }
        }

        /* --- check if this really is an inverse, by multiplying */

        concat_transforms( &ident, transform, inverse );

        if( !close_to_identity(&ident) )
        {
            print( "Error in compute_transform_inverse\n" );
        }
    }
    else
        make_identity_transform( inverse );

    FREE2D( t );
    FREE2D( inv );

    return( success );
}
