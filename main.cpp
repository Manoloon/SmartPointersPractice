#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

class Texture
{
    std::string Path = "";
    public:    
    Texture(const std::string& Path):Path(Path)
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
    std::unordered_map<std::string,int> PathToIdMap;
    int ID = 0;
    public:
    ResourceManager()
    {
       Textures.reserve(100);
    }
    int AddResource(const std::string& Name)
    {
        if(Textures.empty() || !PathToIdMap.contains(Name))
        {
            auto NewTexture = std::make_unique<Texture>(Name);
            Textures.emplace(ID,std::move(NewTexture));
            PathToIdMap.emplace(Name,ID);
            int OldID = ID;
            ID++;
            return OldID;
        }
        return -1;
    }
    Texture* GetTexture(int Id) const 
    {
        auto it = Textures.find(Id);

        if(it != Textures.end())
        {
            return it->second.get();
        }
        else
        {
            std::cout << "Get : Texture with Id:" << Id << " Not Found" << std::endl;
            return nullptr;
        }
        return nullptr;
    }
};

struct RenderComponent
{
    ResourceManager& ReManager;
    explicit RenderComponent(ResourceManager& RM):ReManager(RM){}
    void RenderTexture(int TextureID)
    {
        auto Texture_ptr = ReManager.GetTexture(TextureID);
        if(Texture_ptr)
        {
            std::cout << "Render Texture pointer: " << Texture_ptr << " Path: " << Texture_ptr->GetPath() << "\n";
        }
        else
        {
            std::cout << "Render: Texture with ID :" << TextureID << " Not found!\n";
        }
    }
};


int main()
{
    ResourceManager RM;
    std::string Texture1 = "Texture1";
    std::string Texture2 = "Texture2";
    std::cout << "Add new Resource, got id :" << RM.AddResource(Texture1) << '\n';
    std::cout << "Add new Resource, got id :" << RM.AddResource(Texture2) << '\n';
    std::cout << "Add new Resource, got id :" << RM.AddResource(Texture1) << '\n';
    auto Render = std::make_unique<RenderComponent>(RM);
    Render->RenderTexture(0);
    Render->RenderTexture(1);
    Render->RenderTexture(2);
    return 0;
}