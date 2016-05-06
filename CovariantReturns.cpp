//=============================================================================
//
// 

#include <cassert>

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include <UnitCpp.h>

//=============================================================================
class Image {
public:

  Image();
  
  virtual std::string name() const = 0;

  virtual ~Image() = 0;
};

//=============================================================================
class ImageDatabase {
public:

  ImageDatabase();

  virtual const Image& find(std::string name) const = 0;
  // Finds the named image.
  // Precondition: member(name)

  virtual bool member(std::string name) const = 0;
  // Is the named image a member of ImageDatabase?

  virtual ~ImageDatabase() = 0;
};

//=============================================================================
class EntityDatabase {
public:

  EntityDatabase();
  
  virtual ImageDatabase& image_database() = 0;

  virtual ~EntityDatabase() = 0;
};

//=============================================================================
class MemoryImage : public Image {
public:

  MemoryImage(std::string name);

  MemoryImage(const MemoryImage& other);
  MemoryImage& operator=(const MemoryImage& other);
  
  virtual std::string name() const override;

  virtual ~MemoryImage();
  
private:

  std::string m_name;
};

//=============================================================================
class MemoryImageDatabase : public ImageDatabase {
public:

  MemoryImageDatabase();

  virtual const Image& find(std::string name) const override;
  // Finds the named image.
  // Precondition: member(name)

  virtual bool member(std::string name) const override;
  // Is the named image a member of ImageDatabase?

  void add(MemoryImage image);

  virtual ~MemoryImageDatabase();

private:

  std::vector<MemoryImage>::const_iterator position(std::string name) const;
  
  std::vector<MemoryImage> m_images;
};

//=============================================================================
class MemoryEntityDatabase : public EntityDatabase {
public:

  MemoryEntityDatabase();

  virtual MemoryImageDatabase& image_database() override;
  
  virtual ~MemoryEntityDatabase();
private:

  MemoryImageDatabase m_image_database;
};

//=============================================================================
std::unique_ptr<EntityDatabase> create_database();

//=============================================================================
TEST(CovariantReturns, create_database)
{
  auto database = create_database();
  TEST_TRUE(database);
  ImageDatabase& image_database = database->image_database();
  TEST_TRUE(image_database.member("test"));
}

//=============================================================================
int main(int argc, char** argv) 
{
  return UnitCpp::TestRegister::test_register().run_tests_interactive(argc, argv);
}

//=============================================================================
Image::Image() {}
Image::~Image() {}

//=============================================================================
ImageDatabase::ImageDatabase() {}
ImageDatabase::~ImageDatabase() {}

//=============================================================================
EntityDatabase::EntityDatabase() {}
EntityDatabase::~EntityDatabase() {}

//=============================================================================
MemoryImage::MemoryImage(std::string name)
  : m_name(name)
{
}

//=============================================================================
MemoryImage::MemoryImage(const MemoryImage& other)
  : m_name(other.name())
{
}

//=============================================================================
MemoryImage& MemoryImage::operator=(const MemoryImage& other)
{
  m_name = other.name();
  return *this;
}

//=============================================================================
MemoryImage::~MemoryImage()
{
}

//=============================================================================
std::string MemoryImage::name() const
{
  return m_name;
}

//=============================================================================
MemoryImageDatabase::MemoryImageDatabase() {}
MemoryImageDatabase::~MemoryImageDatabase() {}

//=============================================================================
const Image& MemoryImageDatabase::find(std::string name) const
{
  assert(member(name) && "name not a member.");
  return *(position(name));
}

//=============================================================================
std::vector<MemoryImage>::const_iterator MemoryImageDatabase::position(
  std::string name
) const
{
  auto predicate = [name](const MemoryImage& image){
    return image.name() == name;
  };
  return std::find_if(begin(m_images),end(m_images), predicate);
}

//=============================================================================
bool MemoryImageDatabase::member(std::string name) const
{
  return position(name)!= end(m_images);
}

//=============================================================================
void MemoryImageDatabase::add(MemoryImage image)
{
  m_images.push_back(image);
}

//=============================================================================
MemoryEntityDatabase::MemoryEntityDatabase() {}
MemoryEntityDatabase::~MemoryEntityDatabase() {}

//=============================================================================
MemoryImageDatabase& MemoryEntityDatabase::image_database()
{
  return m_image_database;
}

//=============================================================================
std::unique_ptr<EntityDatabase> create_database()
{
  auto database = std::make_unique<MemoryEntityDatabase>();
  database->image_database().add(MemoryImage("test"));
  return std::move(database);
}

