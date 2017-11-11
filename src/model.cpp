#include <nob/model.hpp>

#include <unordered_map>

namespace nob {
	std::unordered_map<int, size_t> _model_count;

	model::model(const char *name) : _ntv_model(ntv::GAMEPLAY::GET_HASH_KEY(name)) {
		if (ntv::STREAMING::IS_MODEL_IN_CDIMAGE(_ntv_model) && ntv::STREAMING::IS_MODEL_VALID(_ntv_model)) {
			auto it = _model_count.find(_ntv_model);
			if (it == _model_count.end()) {
				it->second = 1;
			} else {
				++it->second;
			}

			ntv::STREAMING::REQUEST_MODEL(_ntv_model);
			if (!ntv::STREAMING::HAS_MODEL_LOADED(_ntv_model)) {
				auto m = _ntv_model;
				wait([m]()->bool {
					return ntv::STREAMING::HAS_MODEL_LOADED(m);
				});
			}
		} else {
			_ntv_model = 0;
		}
	}

	model::model(const model &src) : _ntv_model(src._ntv_model) {
		if (_ntv_model) {
			++_model_count[_ntv_model];
		}
	}

	model &model::operator=(const model &src) {
		free();
		if (src._ntv_model) {
			_ntv_model = src._ntv_model;
			++_model_count[_ntv_model];
		}
		return *this;
	}

	model::model(model &&src) : _ntv_model(src._ntv_model) {
		if (_ntv_model) {
			src._ntv_model = 0;
		}
	}

	model &model::operator=(model &&src) {
		free();
		if (src._ntv_model) {
			_ntv_model = src._ntv_model;
			src._ntv_model = 0;
		}
		return *this;
	}

	void model::free() {
		if (_ntv_model) {
			if (!--_model_count[_ntv_model]) {
				ntv::STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(_ntv_model);
			}
			_ntv_model = 0;
		}
	}

	constexpr std::array<const char *, 696> model::characters;
	constexpr std::array<const char *, 696> model::characters_desc;
	constexpr std::array<const char *, 400> model::vehicles;
} /* nob */
