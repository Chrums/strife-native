#ifndef ISYSTEM_H
#define ISYSTEM_H

#include <type_traits>

namespace Strife {
	namespace Core {

		class Scene;

		class ISystem {

		public:
			template <class S>
			static void AssertBase();

			ISystem(Scene& scene);
			virtual ~ISystem() = default;

		protected:
			Scene& scene_;
		};

		template <class S>
		void ISystem::AssertBase() {
			static_assert(std::is_base_of<ISystem, S>::value, "Type not derived from ISystem");
		}

	}  // namespace Core
}  // namespace Strife

#endif