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
