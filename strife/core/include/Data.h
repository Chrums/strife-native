#ifndef DATA_H
#define DATA_H

#include <memory>
#include <map>
#include <optional>
#include <string>
#include <vector>
#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
#include "Entity.h"

namespace Strife {
	namespace Core {
		
		class Scene;
		
		class Data : public nlohmann::json {
			
			using nlohmann::json::json;
			
		public:
		
			Data();
			Data(const Data& data);
			Data(Scene* const scene);
			Data(const nlohmann::json& j);
			
		private:
		
			Data(Scene* const scene, std::shared_ptr<std::map<boost::uuids::uuid, Entity>> context, const nlohmann::json data);

			Scene* scene_;
        	std::shared_ptr<std::map<boost::uuids::uuid, Entity>> context_;
			
		};
		
	} // namespace Core
}  // namespace Strife

namespace nlohmann {
	
	template <>
	struct adl_serializer<Strife::Core::Data> {

        static void to_json(json& j, const Strife::Core::Data& data) {
			j = nlohmann::json(data);;
		}

        static void from_json(const json& j, Strife::Core::Data& data) {
			data = Strife::Core::Data(j);
		}
		
	};
	
	// template <>
	// struct adl_serializer<boost::uuids::uuid> {

 //       static void to_json(json& data, const boost::uuids::uuid& id) {
	// 		data = boost::lexical_cast<std::string>(id);
	// 	}

 //       static void from_json(const json& data, boost::uuids::uuid& id) {
	// 		id = boost::lexical_cast<boost::uuids::uuid>(data.get<std::string>());
	// 	}
		
	// };

}  // namespace nlohmann

#endif
