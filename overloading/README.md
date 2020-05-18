# Overloading

## "Template Overloading" - Algorithm Specialization

c++ template: complete guide L16387

> however c++ does not current provide any direct way to express overloads
> based on type properties... the names of the template parameters are 
> ignored when comparing two templates

One of the common motivations behind overloading of function templates is
to provide more specialized versions of an algorithm based on knowledge
of the types involved.

see: specialized_swap.cpp

## Tag Dispatching

c++ template: complete guide L16387

(if the partial-specialization technique leads to double definition, use tag 
dispatching)

see: iter_category.cpp

L16481

> tag dispatching works well when there is a natural hierarchical structure to
> the properties used by the algorithm and an existing set of traits that 
> provide those tag values
> it is not as convenient when algorithm specialization depends on ad hoc type
> properties, such as whether the type T has a trivial copy assignment op



