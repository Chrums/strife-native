// #ifndef CONTEXT_H
// #define CONTEXT_H

// #include <memory>
// #include <map>
// #include <optional>
// #include <string>
// #include <vector>
// #include <boost/uuid/uuid.hpp>
// #include <boost/lexical_cast.hpp>
// #include <boost/uuid/uuid_io.hpp>
// #include <nlohmann/json.hpp>
// #include "Entity.h"

// namespace Strife {
//     namespace Core {

//         class Scene;

//         class Context {
            
//         	class Accessor {
        	    
//         	public:
        	
//         	    Accessor(Context& context, std::string identifier)
//         	        : context_(context)
//         	        , identifier_(identifier) {}
        	
//         	    template <typename T>
//         	    T get() {
//         	        return context_.data[identifier_].get<T>();
//         	    }
        	    
//         	    template <typename ...Args>
//         	    nlohmann::json& operator=(Args... args) {
//         	        return context_.data[identifier_].operator=(args...);
//         	    }
        	    
//         	private:
        	
//         	    Context& context_;
//         	    std::string identifier_;
        	    
//         	};
        	
//         public:
        
//         	nlohmann::json data;
        
//             Context();
//         	Context(Scene* scene);
//         	Entity get(const boost::uuids::uuid id);
//         	Context bind(const nlohmann::json data);
//         	Accessor operator[](const std::string identifier);
        	
//         private:
        
//         	Context(Scene* scene, std::shared_ptr<std::map<boost::uuids::uuid, Entity>> context, const nlohmann::json data);
        	
//         	Scene* scene_;
//         	std::shared_ptr<std::map<boost::uuids::uuid, Entity>> context_;
        	
//         };

//         template<>
//         inline std::optional<Entity> Context::Accessor::get() {
//             nlohmann::json data = context_.data[identifier_];
//             if (!data.is_null()) {
//                 const boost::uuids::uuid id = data.get<boost::uuids::uuid>();
//             	return context_.get(id);
//             } else {
//                 return std::nullopt;
//             }
//         }
	
//         inline void to_json(nlohmann::json& data, const std::optional<Entity>& entity) {
// 			if (entity) {
// 				data = entity.value().id;
// 			} else {
// 				data = nullptr;
// 			}
// 	    }
	    
// 	    inline void from_json(const nlohmann::json& data, std::optional<Entity>& entity) {
// 	        entity = std::nullopt;
// 	    }
        
//         template<>
//         inline std::vector<Entity> Context::Accessor::get() {
//             nlohmann::json data = context_.data[identifier_];
//             std::vector<Entity> entities;
//             if (data.is_array()) {
//                 for (auto identifier : data) {
//                     const boost::uuids::uuid id = identifier.get<boost::uuids::uuid>();
//             	    entities.push_back(context_.get(id));
//                 }
//             }
//             return entities;
//         }
	    
// 	    inline void to_json(nlohmann::json& data, const std::vector<Entity>& entities) {
// 			for (const Entity& entity : entities) {
// 				data.push_back(entity.id);
// 			}
// 	    }
	    
// 	    inline void from_json(const nlohmann::json& data, std::vector<Entity>& entities) {}

//     }
// }

// namespace nlohmann {
    
// 	template <>
// 	struct adl_serializer<boost::uuids::uuid> {

//         static void to_json(json& data, const boost::uuids::uuid& id) {
// 			data = boost::lexical_cast<std::string>(id);
// 		}

//         static void from_json(const json& data, boost::uuids::uuid& id) {
// 			id = boost::lexical_cast<boost::uuids::uuid>(data.get<std::string>());
// 		}
		
// 	};

// }  // namespace nlohmann

// #endif