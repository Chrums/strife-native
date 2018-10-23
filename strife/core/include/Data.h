#ifndef DATA_H
#define DATA_H

#include <map>
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
	
	template <>
	struct adl_serializer<Strife::Core::Data> {

        static void to_json(json& j, const Strife::Core::Data& data) {
	        j = nlohmann::json(data);
		}

        static void from_json(const json& j, Strife::Core::Data& data) {
	        data = Strife::Core::Data(j);
		}
		
	};
	
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
