#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

class Texture
{
    std::string Path = "texture";
    public:    
    Texture(const std::string Path):Path(Path)
    {
        if(Path.empty())
        {
            std::cout << "Path is empty\n";
            return;
        }
    }
    std::string GetPath() const {return Path;}
};

class ResourceManager
{
    std::unordered_map<int,std::unique_ptr<Texture>>Textures;
    int ID = 0;
    public:
    ResourceManager()
    {
       Textures.reserve(100);
    }
    void AddResource(const std::string Name)
    {
        auto NewTexture = std::make_unique<Texture>(Name);
        Textures.emplace(ID,std::move(NewTexture));
        ID++;
    }
    Texture* GetTexture(int Id) const 
    {
        if(Textures.contains(Id))
        {
            return Textures.find(Id)->second.get();
        }
        else
        {
            std::cout << "Texture with Id:" << Id << " NOT Found" << std::endl;
            return nullptr;
        }
        return nullptr;
    }
};

struct RenderComponent
{
    std::shared_ptr<ResourceManager> ReManager = nullptr;
    explicit RenderComponent(std::shared_ptr<ResourceManager> RM):ReManager(RM){}
    void RenderTexture(int TextureID)
    {
        auto Texture_ptr = ReManager->GetTexture(TextureID);
        std::cout << "Render Texture pointer: " << Texture_ptr << " Path: " << Texture_ptr->GetPath() << "\n";
    }
};


int main()
{
    auto RM = std::make_shared<ResourceManager>();
    RM->AddResource("Texture1");
    auto Render = std::make_unique<RenderComponent>(RM);
    Render->RenderTexture(0);
    return 0;
}