#ifndef CGAL_KERNEL_D_CARTESIAN_COMPLETE_H
#define CGAL_KERNEL_D_CARTESIAN_COMPLETE_H

#include <CGAL/Kernel_d/function_objects_cartesian.h>
#include <CGAL/Kernel_d/Cartesian_per_dimension.h>
#include <CGAL/Kernel_d/Define_segment.h>
#include <CGAL/Kernel_d/Types/Sphere.h>
#include <CGAL/Kernel_d/Types/Hyperplane.h>
#include <CGAL/Kernel_d/Types/Aff_transformation.h>
#include <CGAL/Kernel_d/Types/Line.h>
#include <CGAL/Kernel_d/Types/Ray.h>
#include <CGAL/Kernel_d/Types/Iso_box.h>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/has_xxx.hpp>


namespace CGAL {

template<class R_,class Derived_> struct Cartesian_define_all_functors_
: public R_
{
	typedef R_ Kernel_base;
	template<class F, class D=void> struct Functor
		: Get_functor<Kernel_base,F,D>
	{ };
#define CGAL_Kernel_cons2(F,f) \
	template<class D> struct Functor <F##_tag,D> { \
		typedef CartesianDKernelFunctors::F<Derived_> type; \
	};
	//type f() const { return type(); }
#define CGAL_Kernel_obj2(X,Y) \
	template<class D> struct Functor <Construct_ttag<X##_tag>,D> { \
		typedef CartesianDKernelFunctors::Construct_##Y<Derived_> type; \
	};
//#define CGAL_Kernel_pred(F,f) CGAL_Kernel_cons2(F,f)
//#define CGAL_Kernel_comp2(F,f) CGAL_Kernel_cons2(F,f)

#include <CGAL/Kernel_d/interface_macros.h>

};

template<class R_,class Derived_> struct Cartesian_define_all_functors
: public Cartesian_per_dimension<typename R_::Default_ambient_dimension,Cartesian_define_all_functors_<R_,Derived_>,Derived_> {};

template<class R_,bool force_=false,class Derived_=Default> struct Cartesian_complete_types 
: public R_
{
  CGAL_CONSTEXPR Cartesian_complete_types(){}
  CGAL_CONSTEXPR Cartesian_complete_types(int d):R_(d){}

	typedef R_ Kernel_base;
	typedef typename Default::Get<Derived_,Cartesian_complete_types>::type Derived;
	template <class T,class=void> struct Type : Get_type<Kernel_base,T> {};
#define CGAL_Kernel_obj2(X,Y) \
	template <class D> struct Type<X##_tag,D> { \
		static const bool inbase = \
	          Provides_type<Kernel_base, X##_tag>::value; \
		typedef Get_type<Kernel_base,X##_tag> B_; \
		typedef typename boost::mpl::if_c<force_||!inbase,Wrap_type<CGAL::X<Derived> >,B_>::type::type type; \
	};
	//Implement by chaining things like Define_segment?
	//FIXME: needs to be conditional!!!
#include <CGAL/Kernel_d/interface_macros.h>
};


template<class R_,bool force_=false,class Derived_=Default> struct Cartesian_complete_constructors 
: public R_
{
  CGAL_CONSTEXPR Cartesian_complete_constructors(){}
  CGAL_CONSTEXPR Cartesian_complete_constructors(int d):R_(d){}

	typedef R_ Kernel_base;
	typedef typename Default::Get<Derived_,Cartesian_complete_constructors>::type Derived;
	template<class F,class D=void,class=typename Get_functor_category<Derived,F>::type> struct Functor :
		Get_functor<R_,F,D> {};
	template<class F,class D> struct Functor<F,D,Construct_tag> {
		typedef typename Get_functor<Kernel_base, F>::type Base_functor;
		typedef typename boost::mpl::if_c<force_||boost::is_same<Base_functor,Null_functor>::value,
			typename Get_functor<Cartesian_define_all_functors<R_,Derived>, F>::type,
			Base_functor>::type type;
	};

};

template<class R_,bool force_=false,class Derived_=Default> struct Cartesian_complete_predicates 
: public R_
{
  CGAL_CONSTEXPR Cartesian_complete_predicates(){}
  CGAL_CONSTEXPR Cartesian_complete_predicates(int d):R_(d){}

	// TODO: this doesn't look like the right place for this typedef...
	typedef CartesianDKernelFunctors::Flat_orientation Flat_orientation;

	typedef R_ Kernel_base;
	typedef typename Default::Get<Derived_,Cartesian_complete_predicates>::type Derived;
	template<class F,class D=void,class=typename Get_functor_category<Derived,F>::type> struct Functor :
		Get_functor<R_,F,D> {};
	template<class F,class D> struct Functor<F,D,Predicate_tag> {
		typedef typename Get_functor<Kernel_base, F>::type Base_functor;
		typedef typename boost::mpl::if_c<force_||boost::is_same<Base_functor,Null_functor>::value,
			typename Get_functor<Cartesian_define_all_functors<R_,Derived>, F>::type,
			Base_functor>::type type;
	};

};

template<class R_,bool force_=false,class Derived_=Default> struct Cartesian_complete_computes 
: public R_
{
  CGAL_CONSTEXPR Cartesian_complete_computes(){}
  CGAL_CONSTEXPR Cartesian_complete_computes(int d):R_(d){}

	typedef R_ Kernel_base;
	typedef typename Default::Get<Derived_,Cartesian_complete_computes>::type Derived;
	template<class F,class D=void,class=typename Get_functor_category<Derived,F>::type> struct Functor :
		Get_functor<R_,F,D> {};
	template<class F,class D> struct Functor<F,D,Compute_tag> {
		typedef typename Get_functor<Kernel_base, F>::type Base_functor;
		typedef typename boost::mpl::if_c<force_||boost::is_same<Base_functor,Null_functor>::value,
			typename Get_functor<Cartesian_define_all_functors<R_,Derived>, F>::type,
			Base_functor>::type type;
	};

};

}

#endif // CGAL_KERNEL_D_CARTESIAN_COMPLETE_H
