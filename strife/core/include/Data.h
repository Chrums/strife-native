#ifndef DATA_H
#define DATA_H

#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
#include <nlohmann/detail/meta/type_traits.hpp>
#include <nlohmann/detail/meta/cpp_future.hpp>
#include <iostream>

#include "EntityMap.h"

namespace Strife {
    namespace Core {
        template <typename T, typename>
        struct another_adl_serializer;

        using Data = nlohmann::basic_json<std::map, std::vector, std::string, bool, std::int64_t, std::uint64_t, double, std::allocator, another_adl_serializer>;  // {
                                                                                                                                                                   //        public:
                                                                                                                                                                   //            //EntityMap entityMap;
                                                                                                                                                                   //        };

        template <typename T, typename>
        struct another_adl_serializer {
            //template <typename, typename U = T, nlohmann::detail::enable_if_t<!nlohmann::detail::is_compatible_object_type<Data, U>::value, int> = 0>
            static void from_json(const Data& j, T& t) {
                using nlohmann::from_json;
                from_json(j, t);
            }

            static void to_json(Data& j, const T& t) {
                using nlohmann::to_json;
                to_json(j, t);
            }

            //template <typename, typename U = T, nlohmann::detail::enable_if_t<nlohmann::detail::is_compatible_object_type<Data, U>::value, int> = 0>
            //            static void from_json(const Data& j, Data& obj) {
            //                //                if (JSON_UNLIKELY(not j.is_object())) {
            //                //                    JSON_THROW(type_error::create(302, "type must be object, but is " + std::string(j.type_name())));
            //                //                }

            //                auto inner_object = j.template get_ptr<const typename Data::object_t*>();
            //                using value_type = typename Data::value_type;
            //                std::transform(inner_object->begin(), inner_object->end(), std::inserter(obj, obj.begin()),
            //                               [](typename Data::object_t::value_type const& p) {
            //                    return value_type(p.first, p.second.template get<typename Data::mapped_type>());
            //                });
            //            }
        };
    }  // namespace Core
}  // namespace Strife

namespace nlohmann {

	template <>
	struct adl_serializer<boost::uuids::uuid> {

        static void to_json(json& j, const boost::uuids::uuid& id) {
			j = boost::lexical_cast<std::string>(id);
		}

        static void from_json(const json& j, boost::uuids::uuid& id) {
			id = boost::lexical_cast<boost::uuids::uuid>(j.get<std::string>());
        }
    };

}  // namespace nlohmann

#endif
