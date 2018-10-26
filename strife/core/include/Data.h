#ifndef DATA_H
#define DATA_H

#include <map>
#include <optional>
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>

namespace Strife {
	namespace Core {
		
		using Data = nlohmann::json;
		
	} // namespace Core
}  // namespace Strife

namespace nlohmann {
	
	// template <typename T>
	// struct adl_serializer<std::optional<T>> {

 //       void to_json(Strife::Core::Data& data, const std::optional<T>& optional) {
	// 		if (optional) {
	// 			data = optional.value();
	// 		} else {
	// 			data = nullptr;
	// 		}
	//     }
	    
	//     void from_json(const Strife::Core::Data& data, std::optional<T>& optional) {
	//         if (!data.is_null()) {
	//         	optional = data.get<T>();
	//         } else {
	//         	optional = std::nullopt;
	//         }
	//     }
		
	// };
	
	template <>
	struct adl_serializer<boost::uuids::uuid> {

        static void to_json(Strife::Core::Data& data, const boost::uuids::uuid& id) {
			data = boost::lexical_cast<std::string>(id);
		}

        static void from_json(const Strife::Core::Data& data, boost::uuids::uuid& id) {
			id = boost::lexical_cast<boost::uuids::uuid>(data.get<std::string>());
		}
		
	};

}  // namespace nlohmann

#endif
