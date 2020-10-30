#include <iterator>


/**
 * A random access iterator which jumps to another item at a definable distance.
 */
template<class RandAccessIterator>
class SkipIterator {

public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type =
        typename std::iterator_traits<RandAccessIterator>::value_type;
    using difference_type =
        typename std::iterator_traits<RandAccessIterator>::difference_type;
    using pointer = value_type *;
    using reference = value_type &;

private:
    RandAccessIterator iter;
    difference_type spacing;

public:
    /**
     * Constructs a SkipIterator with an initial spacing.
     *
     * @param spacing The skip distance.
     */
    explicit SkipIterator(difference_type spacing = 1);
    /**
     * Constructs a SkipIterator with an initial location and spacing.
     *
     * @param iterator The initial location.
     * @param spacing The skip distance.
     */
    SkipIterator(RandAccessIterator iterator, difference_type spacing = 1);
    /**
     * A copy constructor.
     *
     * @param iterator The iterator to copy.
     */
    SkipIterator(const SkipIterator & iterator);

    reference operator*(void) const;
    SkipIterator operator+(int) const;
    SkipIterator & operator++(void);
    SkipIterator operator++(int);
    SkipIterator & operator+=(difference_type);
    SkipIterator operator-(int) const;
    difference_type operator-(SkipIterator) const;
    SkipIterator & operator--(void);
    SkipIterator operator--(int);
    SkipIterator & operator-=(difference_type);
    bool operator!=(SkipIterator &) const;
    bool operator<(SkipIterator &) const;
    bool operator<=(SkipIterator &) const;
    bool operator==(SkipIterator &) const;
    bool operator>(SkipIterator &) const;
    bool operator>=(SkipIterator &) const;
    reference operator[](difference_type) const;

    /**
     * @return The underlying non-skipping iterator.
     */
    const RandAccessIterator & get(void) const;
    /**
     * @return The skip distance.
     */
    const difference_type & getSpacing(void) const;
    /**
     * Sets the position of the iterator.
     *
     * @param iterator An iterator at the position.
     */
    void set(const RandAccessIterator & iterator);
    /**
     * @param spacing The skip distance.
     */
    void setSpacing(const difference_type & spacing);
};


template<class RandAccessIterator>
SkipIterator<RandAccessIterator>::SkipIterator(
    typename std::iterator_traits<RandAccessIterator>::difference_type spacing
): iter(), spacing(spacing) {
}

template<class RandAccessIterator>
SkipIterator<RandAccessIterator>::SkipIterator(
    RandAccessIterator iterator,
    typename std::iterator_traits<RandAccessIterator>::difference_type spacing
):
    iter(iterator), spacing(spacing)
{
}

template<class RandAccessIterator>
SkipIterator<RandAccessIterator>::SkipIterator(
    const SkipIterator<RandAccessIterator> & iterator
): iter(iterator.iter), spacing(iterator.spacing) {
}

template<class RandAccessIterator>
typename SkipIterator<RandAccessIterator>::reference
SkipIterator<RandAccessIterator>::operator*(void) const {
    return *iter;
}

template<class RandAccessIterator>
SkipIterator<RandAccessIterator>
SkipIterator<RandAccessIterator>::operator+(int amount) const {
    SkipIterator<RandAccessIterator> copy(*this);
    copy.iter += amount * copy.spacing;
    return copy;
}

template<class RandAccessIterator>
SkipIterator<RandAccessIterator> &
SkipIterator<RandAccessIterator>::operator++(void) {
    iter += spacing;
    return *this;
}

template<class RandAccessIterator>
SkipIterator<RandAccessIterator>
SkipIterator<RandAccessIterator>::operator++(int) {
    SkipIterator<RandAccessIterator> copy(*this);
    operator++();
    return copy;
}

template<class RandAccessIterator>
SkipIterator<RandAccessIterator> &
SkipIterator<RandAccessIterator>::operator+=(
    typename SkipIterator<RandAccessIterator>::difference_type amount
) {
    iter += amount * spacing;
    return *this;
}

template<class RandAccessIterator>
SkipIterator<RandAccessIterator>
SkipIterator<RandAccessIterator>::operator-(int amount) const {
    SkipIterator<RandAccessIterator> copy(*this);
    copy.iter -= amount * copy.spacing;
    return copy;
}

template<class RandAccessIterator>
typename SkipIterator<RandAccessIterator>::difference_type
SkipIterator<RandAccessIterator>::operator-(
    SkipIterator<RandAccessIterator> other
) const {
    return (iter - other.iter) / spacing;
}

template<class RandAccessIterator>
SkipIterator<RandAccessIterator> &
SkipIterator<RandAccessIterator>::operator--(void) {
    iter -= spacing;
    return *this;
}

template<class RandAccessIterator>
SkipIterator<RandAccessIterator>
SkipIterator<RandAccessIterator>::operator--(int) {
    SkipIterator<RandAccessIterator> copy(*this);
    operator--();
    return copy;
}

template<class RandAccessIterator>
SkipIterator<RandAccessIterator> &
SkipIterator<RandAccessIterator>::operator-=(
    typename SkipIterator<RandAccessIterator>::difference_type amount
) {
    iter -= amount * spacing;
    return *this;
}

template<class RandAccessIterator>
bool SkipIterator<RandAccessIterator>::operator!=(SkipIterator & other) const {
    return iter != other.iter;
}

template<class RandAccessIterator>
bool SkipIterator<RandAccessIterator>::operator<(SkipIterator & other) const {
    return iter < other.iter;
}

template<class RandAccessIterator>
bool SkipIterator<RandAccessIterator>::operator<=(SkipIterator & other) const {
    return iter < other.iter;
}

template<class RandAccessIterator>
bool SkipIterator<RandAccessIterator>::operator==(SkipIterator & other) const {
    return iter == other.iter;
}

template<class RandAccessIterator>
bool SkipIterator<RandAccessIterator>::operator>(SkipIterator & other) const {
    return iter > other.iter;
}

template<class RandAccessIterator>
bool SkipIterator<RandAccessIterator>::operator>=(SkipIterator & other) const {
    return iter >= other.iter;
}

template<class RandAccessIterator>
typename SkipIterator<RandAccessIterator>::reference
SkipIterator<RandAccessIterator>::operator[](
    typename SkipIterator<RandAccessIterator>::difference_type offset
) const {
    return iter[offset * spacing];
}

template<class RandAccessIterator>
const RandAccessIterator & SkipIterator<RandAccessIterator>::get(void) const {
    return iter;
}

template<class RandAccessIterator>
const typename std::iterator_traits<RandAccessIterator>::difference_type &
SkipIterator<RandAccessIterator>::getSpacing(void) const {
    return spacing;
}

template<class RandAccessIterator>
void SkipIterator<RandAccessIterator>::set(
    const RandAccessIterator & iterator
) {
    iter = iterator;
}

template<class RandAccessIterator>
void
SkipIterator<RandAccessIterator>::setSpacing(
    const typename std::iterator_traits<RandAccessIterator>::difference_type & spacing
) {
    this->spacing = spacing;
}

template<class RandAccessIterator>
SkipIterator<RandAccessIterator>
operator+(int amount, SkipIterator<RandAccessIterator> skip_iterator) {
    return SkipIterator<RandAccessIterator>(
        skip_iterator.get() + amount * skip_iterator.getSpacing(),
        skip_iterator.getSpacing()
    );
}
