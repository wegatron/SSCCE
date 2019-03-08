#include <cstdio>
#include <cassert>
#include <iostream>

template <size_t size>
struct Int2Type
{
	enum { Value = size };
};

template <int index, typename type>
bool pb_write(FILE* out_file, type& obj, Int2Type<index> ind)
{
	pb_write(out_file, obj, Int2Type<index - 1>());
	// write index
	auto info = obj.data.getInfo(Int2Type<index>());
	if (info.second <= 0) return true; // basic type (writed in head), or empty array
	fwrite(info.first, sizeof(*info.first), info.second, out_file);
	return true;
}

template <typename type>
bool pb_write(FILE* out_file, type& obj, Int2Type<0> ind)
{
	// write xxx
	auto info = obj.data.getInfo(Int2Type<0>());
	if (info.second <= 0) return true; // basic type (writed in head), or empty array
	fwrite(info.first, sizeof(*info.first), info.second, out_file);
	return true;
}

/**
* \brief update data's pointer value, use offset as first pointer's address
*/
template <int index, typename type>
bool pb_undate_head(type& head, Int2Type<index> ind, unsigned char * & offset)
{
	pb_undate_head(head, Int2Type<index - 1>(), offset);
	auto info = head.getInfo(Int2Type<index>());
	if (info.second <= 0) return true; // basic type or empty array
	info.first = reinterpret_cast<decltype(info.first)>(offset);
	offset = reinterpret_cast<unsigned char *>(info.first + info.second); // update to unsigned char * pointer
   return true;
}

template<int index, typename type>
void pb_delete_element(type &head, Int2Type<index> ind)
{
   pb_delete_element(head, Int2Type<index - 1>());
   auto info = head.getInfo(Int2Type<index>());
   if (info.second <= 0) return; // basic type or empty array
   assert(info.first != nullptr);
   delete [] info.first;
   info.first = nullptr;
}

template<typename type>
void pb_delete_element(type &head, Int2Type<0> ind)
{
   auto info = head.getInfo(Int2Type<0>());
   if (info.second <= 0) return; // basic type or empty array
   assert(info.first != nullptr);
   delete [] info.first;
   info.first = nullptr;
}

template <typename type>
bool pb_delete_data(type &pb)
{
   if (pb.data_ptr != nullptr)  delete[] pb.data_ptr;
   else pb_delete_element(pb.data, Int2Type<pb.PB_SIZE - 1>());
   return true;
}


template<typename type, int size>
void pb_copy_element(Int2Type<size> ind, type &pb_from, type &pb_to)
{
   pb_copy_element(Int2Type<size-1>(), pb_from, pb_to);
   auto info_from = pb_from.data.getInfo(Int2Type<size>());
   auto info_to = pb_to.data.getInfo(Int2Type<size>());
   if (info_from.second <= 0) return; // basic type or empty array
   assert(info_from.first != nullptr);
   info_to.first = new std::remove_reference<decltype(*info_to.first)>::type [info_from.second];
   memcpy(info_to.first, info_from.first, info_from.second * sizeof(*info_from.first));
}

template<typename type>
void pb_copy_element(Int2Type<0> ind, type &pb_from, type &pb_to)
{
   auto info_from = pb_from.data.getInfo(Int2Type<0>());
   auto info_to = pb_to.data.getInfo(Int2Type<0>());
   if (info_from.second <= 0) return; // basic type or empty array
   assert(info_from.first != nullptr);
   info_to.first = new std::remove_reference<decltype(*info_to.first)>::type[info_from.second];
   memcpy(info_to.first, info_from.first, info_from.second * sizeof(*info_from.first));
}


/**
* \brief update data's pointer value, use offset as first pointer's address
*/
template <typename type>
bool pb_undate_head(type& head, Int2Type<0> ind, unsigned char * & offset)
{
	auto info = head.getInfo(Int2Type<0>());
	if (info.second <= 0) return true; // basic type or empty array
	info.first = reinterpret_cast<decltype(info.first)>(offset);
   offset = reinterpret_cast<unsigned char*>(info.first + info.second); // update to unsigned char * pointer
   return true;
}

#define PB_DEFINE_BEGIN(CLASS_NAME) class CLASS_NAME { struct Header{
#define PB_ARRAY(TYPE, NAME) int num_##NAME = 0; TYPE * NAME = NULL; \
	std::pair<TYPE*&, int> getInfo(Int2Type<__COUNTER__>) { return std::pair<TYPE*&, int>(NAME, num_##NAME); }
#define PB_VAL(TYPE, NAME) TYPE NAME = 0; std::pair<TYPE*, int> getInfo(Int2Type<__COUNTER__>) { return std::make_pair(&NAME, 0); }
#define PB_DEFINE_END(CLASS_NAME) }; public: enum { PB_SIZE = __COUNTER__ }; bool is_own_data; Header data; unsigned char* data_ptr; \
   void serialize(FILE* out_file) \
   { \
       Header serialize_head = data; \
       unsigned char * init_pos = NULL; \
       pb_undate_head(serialize_head, Int2Type<PB_SIZE - 1>(), init_pos); /* update to reference pointer address */ \
       fwrite(&serialize_head, sizeof(Header), 1, out_file); /* write body */ \
       pb_write(out_file, *this, Int2Type<PB_SIZE - 1>()); \
   } \
   void parse(unsigned char* in_data, bool own_data) \
   { \
       is_own_data = own_data; \
       data_ptr = in_data; \
       /* parse data */ \
       memcpy(&data, in_data, sizeof(Header));  /* parse body */ \
       unsigned char * init_pos = in_data + sizeof(Header); \
       pb_undate_head(data, Int2Type<PB_SIZE - 1>(), init_pos); \
   } \
   CLASS_NAME() : is_own_data(false), data_ptr(nullptr) {} \
   ~CLASS_NAME() { if (is_own_data) pb_delete_data(*this); } \
   CLASS_NAME * clone(bool is_deep_copy) { CLASS_NAME * npb = new CLASS_NAME(*this); npb->is_own_data = is_deep_copy; if(is_deep_copy) { npb->data_ptr = nullptr; pb_copy_element(Int2Type<PB_SIZE-1>(), *this, *npb); } return npb; } \
   private: \
   CLASS_NAME(const CLASS_NAME &t) = default; \
   CLASS_NAME & operator=(const CLASS_NAME & t) = default; \
   };

PB_DEFINE_BEGIN(SpeckleBuildData)
PB_VAL(int, tv)
PB_ARRAY(double, vertices)
PB_ARRAY(int, normals)
PB_DEFINE_END(SpeckleBuildData)

int main(int argc, char* argv[])
{
   // int * ptr = new int[10];
   // int * & ptr2 = ptr;
   // delete [] ptr2;
   // ptr2 = nullptr;
   SpeckleBuildData spd;
   spd.data.tv = 100;
   spd.data.num_vertices = 10;
   spd.data.vertices = new double[spd.data.num_vertices];
   for (int i = 0; i<10; ++i)
   {
       spd.data.vertices[i] = i;
   }
   spd.data.vertices[0] = 100.8;

   spd.data.num_normals = 5;
   spd.data.normals = new int[spd.data.num_normals];
   for (int i = 0; i<spd.data.num_normals; ++i)
   {
       spd.data.normals[i] = i;
   }
   spd.data.normals[0] = 1087;

	FILE* out_file = nullptr;
	fopen_s(&out_file, "d:/test.spd", "wb");
	spd.serialize(out_file);
	fclose(out_file);

   FILE * in_file = nullptr;
   fopen_s(&in_file, "d:/test.spd", "rb");
   _fseeki64(in_file, 0, SEEK_END);
   const long long file_size = _ftelli64(in_file);
   _fseeki64(in_file, 0, SEEK_SET);
   unsigned char * data = new unsigned char[file_size];
   fread(data, sizeof(unsigned char), file_size, in_file);
   spd.parse(data, true);

   SpeckleBuildData * spc_deep = spd.clone(true);
   SpeckleBuildData * spc_shallow = spd.clone(false);
   delete spc_deep;
   delete spc_shallow;
   // std::string a;
   // int ind = a.find_first_of('_', 0);
   // std::cout << ind << std::endl;
	return 0;
}
