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

namespace nlohmann {
	
	template <>
	struct adl_serializer<boost::uuids::uuid> {

        static void to_json(json& data, const boost::uuids::uuid& id) {
			data = boost::lexical_cast<std::string>(id);
		}

        static void from_json(const json& data, boost::uuids::uuid& id) {
			id = boost::lexical_cast<boost::uuids::uuid>(data.get<std::string>());
		}
		
	};

}  // namespace nlohmann

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
			
			Entity get(const boost::uuids::uuid id);
			Data bind(const Data& data);
			
			template <typename T>
			Data operator[](const T& value) {
				return Data(nlohmann::json::operator[](value));
			}
			
		private:
		
			Data(Scene* const scene, std::shared_ptr<std::map<boost::uuids::uuid, Entity>> context, const nlohmann::json& j);

			Scene* scene_;
        	std::shared_ptr<std::map<boost::uuids::uuid, Entity>> context_;
			
		};
		
		inline void to_json(nlohmann::json& j, const Data& data) {
			j = nlohmann::json(data);
	    }
	    
	    inline void from_json(const nlohmann::json& j, Data& data) {
	        data = Data(j);
	    }
	
        inline void to_json(nlohmann::json& data, const std::optional<Entity>& entity) {
			if (entity) {
				data = entity.value().id;
			} else {
				data = nullptr;
			}
	    }
	    
	    inline void from_json(const nlohmann::json& data, std::optional<Entity>& entity) {
	        entity = std::nullopt;
	    }
        
        // template<>
        // inline std::vector<Entity> Context::Accessor::get() {
        //     nlohmann::json data = context_.data[identifier_];
        //     std::vector<Entity> entities;
        //     if (data.is_array()) {
        //         for (auto identifier : data) {
        //             const boost::uuids::uuid id = identifier.get<boost::uuids::uuid>();
        //     	    entities.push_back(context_.get(id));
        //         }
        //     }
        //     return entities;
        // }
	    
	    inline void to_json(nlohmann::json& data, const std::vector<Entity>& entities) {
			for (const Entity& entity : entities) {
				data.push_back(entity.id);
			}
	    }
	    
	    inline void from_json(const nlohmann::json& data, std::vector<Entity>& entities) {
	    	entities = std::vector<Entity>();
	    }
		
	} // namespace Core
}  // namespace Strife

#endif
