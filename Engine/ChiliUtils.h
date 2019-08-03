#pragma once

namespace chili
{
	// remove an element from a vector
	// messes up the order of elements
	// (faster than erase and doesn't need iter)
	template<typename T>
	inline void remove_element( std::vector<T>& vec,size_t index )
	{
		// swap element to be removed with element at back
		std::swap( vec[index],vec.back() );
		// back is now what we want dead, so pop back!
		vec.pop_back();
	}

	// uses remove_if to remove elements matching predicate over entire container
	// and then calls erase to remove the 'empty' husks at the end
	template<class Container,class Pred>
	void remove_erase_if( Container& container,Pred pred )
	{
		// this destroys all elements matching the predicate
		// and fills the spaces with elements from the end
		const auto new_end = std::remove_if( container.begin(),container.end(),pred );
		// erase garbage husk element at end
		container.erase( new_end,container.end() );
	}
}