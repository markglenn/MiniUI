#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

#include "../Exception.h"

namespace MiniUI
{
	namespace Types
	{
		template <class t> class Vector2D
		{
			public:
				t x, y;

				Vector2D ( ) : x((t)0.0), y((t)0.0)				{}
				Vector2D ( t x, t y ) : x(x), y(y)				{}
				Vector2D ( const Vector2D<t>& v ) : x(v.x), y(v.y)	{}

				virtual ~Vector2D ( ) {}

				///////////////////////////////////////////////////////////////////
				t SquaredLength ( )
					///////////////////////////////////////////////////////////////////
				{
					return (x * x) + (y * y);
				}

				///////////////////////////////////////////////////////////////////
				t Length ( )
				///////////////////////////////////////////////////////////////////
				{
					//return Math<t>::SquareRoot ( SquaredLength ( ) );
				}

				///////////////////////////////////////////////////////////////////
				t& operator[] ( int index )
				///////////////////////////////////////////////////////////////////
				{
					switch ( index )
					{
						case 0:
							return x;
						case 1:
							return y;
					}

					throw IndexOutOfRangeException( );

					return x;
				}

				///////////////////////////////////////////////////////////////////
				static t Dot ( Vector2D<t> v1, Vector2D<t> v2 )
				///////////////////////////////////////////////////////////////////
				{
					return v1.x * v2.x + v1.y * v2.y;
				}

				///////////////////////////////////////////////////////////////////
				Vector2D<t> Normalized ()
				///////////////////////////////////////////////////////////////////
				{
					t length = this->Length();

					// Will also work for zero-sized vectors, but will change nothing
					if ( length > (t)0.0001f )
					{
						t inverseLength = (t)(1.0f) / length;
						return Vector2D<t> ( x * inverseLength, y * inverseLength );
					}

					return *this;
				}

				///////////////////////////////////////////////////////////////////
				void Set ( t x, t y )
				///////////////////////////////////////////////////////////////////
				{
					this->x = x;
					this->y = y;
				}

			/*

			/// <summary>
			/// Reflects a vector on a plane
			/// </summary>
			/// <param name="plane">The plane to reflect from</param>
			/// <returns>A reflected vector</returns>
				public Vector3 Reflection(Plane plane)
				{
				return this - (2 * Vector3.Dot(this, plane.Normal) * plane.Normal);
		}

				#endregion
			*/
		};

		///////////////////////////////////////////////////////////////////////
		template <class t>
		inline bool operator == ( Vector2D<t> v1, Vector2D<t> v2 )
		///////////////////////////////////////////////////////////////////////
		{
			return (v1.x == v2.x) && (v2.y == v2.y);
		}

		///////////////////////////////////////////////////////////////////////
		template <class t>
		inline bool operator != ( Vector2D<t> v1, Vector2D<t> v2 )
		///////////////////////////////////////////////////////////////////////
		{
			return !(v1 == v2 );
		}

		///////////////////////////////////////////////////////////////////////
		template <class t>
		inline Vector2D<t> operator + (Vector2D<t> lhs, Vector2D<t> rhs)
		///////////////////////////////////////////////////////////////////////
		{
			return Vector2D<t> (lhs.x + rhs.x, lhs.y + rhs.y);
		}

		///////////////////////////////////////////////////////////////////////
		template <class t>
		inline Vector2D<t> operator - (Vector2D<t> lhs, Vector2D<t> rhs)
		///////////////////////////////////////////////////////////////////////
		{
			return Vector2D<t> (lhs.x - rhs.x, lhs.y - rhs.y);
		}

		///////////////////////////////////////////////////////////////////////
		template <class t>
		inline Vector2D<t> operator * (Vector2D<t> lhs, t rhs)
		///////////////////////////////////////////////////////////////////////
		{
			return Vector2D<t> (lhs.x * rhs, lhs.y * rhs);
		}

		///////////////////////////////////////////////////////////////////////
		template <class t>
		inline Vector2D<t> operator * (t lhs, Vector2D<t> rhs)
		///////////////////////////////////////////////////////////////////////
		{
			return rhs * lhs;
		}

		///////////////////////////////////////////////////////////////////////
		template <class t>
		inline t operator * (Vector2D<t> lhs, Vector2D<t> rhs)
		///////////////////////////////////////////////////////////////////////
		{
			return Vector2D<t>::Dot (lhs, rhs);
		}

		///////////////////////////////////////////////////////////////////////
		template <class t>
		inline Vector2D<t> operator / (Vector2D<t> lhs, t rhs)
		///////////////////////////////////////////////////////////////////////
		{
			return Vector2D<t> (lhs.x / rhs, lhs.y / rhs);
		}

		///////////////////////////////////////////////////////////////////////
		template <class t>
		inline Vector2D<t> operator / (t lhs, Vector2D<t> rhs)
		///////////////////////////////////////////////////////////////////////
		{
			return rhs / lhs;
		}

	}
}

#endif // _VECTOR2D_H_
