#ifndef UNIQUE_H
#define UNIQUE_H

#include <functional>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/functional/hash.hpp>

namespace Strife {
	namespace Core {

		class Unique {

		public:
			static boost::uuids::nil_generator NilGenerator;
			static boost::uuids::random_generator RandomGenerator;

			static Unique Nil();
			static Unique Random();

			boost::uuids::uuid id;

			Unique(const Unique& unique);
			Unique();
			Unique(const boost::uuids::uuid id);

			bool operator==(const Unique& unique) const;
            bool operator<(const Unique& unique) const;
		};

	}  // namespace Core
}  // namespace Strife

namespace std {
    template <>
    struct hash<Strife::Core::Unique> {
        size_t operator()(const Strife::Core::Unique& unique) {
            return boost::hash<boost::uuids::uuid>{}(unique.id);
        }
    };
}  // namespace std

#endif
