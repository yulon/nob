#pragma once

#include <cstdint>
#include <cassert>
#include <array>

namespace nob {
	namespace ntv {
		// Reference from http://www.dev-c.com/gtav/scripthookv/

		typedef unsigned int Void;
		typedef unsigned int Any;
		typedef unsigned int uint;
		typedef unsigned int Hash;
		typedef int Entity;
		typedef int Player;
		typedef int FireId;
		typedef int Ped;
		typedef int Vehicle;
		typedef int Cam;
		typedef int CarGenerator;
		typedef int Group;
		typedef int Train;
		typedef int Pickup;
		typedef int Object;
		typedef int Weapon;
		typedef int Interior;
		typedef int Blip;
		typedef int Texture;
		typedef int TextureDict;
		typedef int CoverPoint;
		typedef int Camera;
		typedef int TaskSequence;
		typedef int ColourIndex;
		typedef int Sphere;
		typedef int ScrHandle;

		#pragma pack(push, 1)
		typedef struct
		{
			float x;
			unsigned int _paddingx;
			float y;
			unsigned int _paddingy;
			float z;
			unsigned int _paddingz;
		} Vector3;
		#pragma pack(pop)

		////////////////////////////////////////////////////////////////////////////

		// Reference from https://github.com/zorg93/EnableMpCars-GTAV

		class global_table_t {
			public:
				global_table_t();

				uint64_t &operator[](uint32_t hash) {
					#ifdef DEBUG
						assert(*this);
					#endif

					return _base_addr[hash >> 18 & 0x3F][hash & 0x3FFFF];
				}

				uint64_t operator[](uint32_t hash) const {
					return (*this)[hash];
				}

				operator bool() const {
					return _base_addr && *_base_addr;
				}

			private:
				uint64_t **_base_addr;
		};

		struct script_t {
			char padding1[16];					//0x0
			uint8_t **blocks_offset;		//0x10
			char padding2[4];					//0x18
			int length;							//0x1C
			char padding3[4];					//0x20
			int local_count;					//0x24
			char padding4[4];					//0x28
			int native_count;					//0x2C
			int64_t *local_offset;				//0x30
			char padding5[8];					//0x38
			int64_t *native_offset;				//0x40
			char padding6[16];					//0x48
			int nameHash;						//0x58
			char padding7[4];					//0x5C
			char *name;							//0x60
			char **strings_offset;				//0x68
			int string_size;					//0x70
			char padding8[12];					//0x74

			bool is_valid() const {
				return length;
			}

			int page_count() const {
				return (length + 0x3FFF) >> 14;
			}

			int page_size(int page) const {
				return (page < 0 || page >= page_count() ? 0 : (page == page_count() - 1) ? length & 0x3FFF : 0x4000);
			}

			uint8_t *page_addr(int page) const {
				return blocks_offset[page];
			}

			uint8_t *pos_addr(int pos) const {
				return pos < 0 || pos >= length ? NULL : &blocks_offset[pos >> 14][pos & 0x3FFF];
			}

			char* get_string(int str_pos) const {
				return str_pos < 0 || str_pos >= string_size ? NULL : &strings_offset[str_pos >> 14][str_pos & 0x3FFF];
			}
		};

		struct script_list_t {
			struct node_t {
				script_t *script;
				int _unk;
				int hash;
			};

			node_t *nodes;
			uint8_t _unk[16];
			int size;

			node_t *find(const char *name) const;
		};

		////////////////////////////////////////////////////////////////////////////

		// Reference from https://github.com/ivanmeler/OpenVHook

		class func_t {
			public:
				operator bool() {
					return _ptr;
				}

				bool operator==(func_t f) const {
					return _ptr == f._ptr;
				}

				bool operator!=(func_t f) const {
					return _ptr != f._ptr;
				}

				template <uint8_t N>
				uintptr_t call(std::array<uintptr_t, N> args) {
					if (!_ptr) {
						return 0;
					}

					_call_context_t cc;
					uintptr_t result;
					cc.args_len = args.size();
					if (args.size()) {
						cc.args = args.data();
						cc.result = args.data();
					} else {
						cc.args = &result;
						cc.result = &result;
					}
					_ptr(&cc);
					return cc.result[0];
				}

			private:
				struct _call_context_t {
					uintptr_t *result;
					uint32_t args_len;
					uintptr_t *args;
					uint32_t data_len = 0;
				};

				void (__cdecl *_ptr)(_call_context_t *cc) = nullptr;
		};

		static func_t nullfunc;

		class func_table_t {
			public:
				struct node_t {
					node_t *next_node;
					func_t funcs[7];
					uint32_t length;
					uint64_t hashes[7];
				};

				func_table_t();

				func_t &operator[](uint64_t hash) {
					if (!_nodes) {
						return nullfunc;
					}
					for (auto n = _nodes[hash & 0xFF]; n; n = n->next_node) {
						for (uint8_t i = 0; i < n->length; ++i) {
							if (n->hashes[i] == hash) {
								return n->funcs[i];
							}
						}
					}
					return nullfunc;
				}

				func_t operator[](uint64_t hash) const {
					return (*this)[hash];
				}

				operator bool() const {
					return _nodes;
				}

			private:
				node_t **_nodes;
		};
	} /* ntv */
} /* nob */
