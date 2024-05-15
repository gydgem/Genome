//
// Created by gydgem on 09.05.24.
//

#ifndef GENOME_GENOME_H
#define GENOME_GENOME_H


#include "genome_common.h"
#include "gene.h"

namespace hgem {
    class genome {
    private:
        std::unordered_map<std::string, size_t> genes_id;
        std::vector<std::any> genes;
    public:
        genome() = default;

        virtual ~genome() = default;

    public:
        [[nodiscard]] size_t size() const {
            return genes.size();
        }

        [[nodiscard]]std::vector<std::pair<std::string, size_t>> Get_name_genes() const {
            std::vector<std::pair<std::string, size_t>> res;
            for (auto &iter: genes_id)
                res.emplace_back(iter);
            return res;
        }

    public:
        template<class Type_value = genome>
        Type_value &at(const std::string& name) {
            if (genes_id.find(name) == genes_id.end())
                throw std::out_of_range("Name not found");
            return std::any_cast<Type_value&>(genes[genes_id[name]]);
        }

        template<class Type_value = genome>
        Type_value &at(size_t id){
            if (genes.size() <= id)
                throw std::out_of_range("Id not found");
            return std::any_cast<Type_value&>(genes.at(id));
        }

    public:
        template<class Type_value = genome>
        Type_value &operator[](const std::string &name){
            return at<Type_value>(name);
        }

        template<class Type_value = genome>
        Type_value &operator[](size_t id){
            return std::any_cast<Type_value&>(genes[id]);
        }

    public:
        [[maybe_unused]] void push(const std::string &name) {
            if (genes_id.find(name) != genes_id.end())
                throw std::out_of_range("attempt to change a gene.");
            genes_id[name] = genes.size();
            genes.emplace_back();
        }

        template<class Type>
        [[maybe_unused]] void push(const std::string &name,const Type &value) {
            push(name);
            set(genes_id[name], value);
        }

    public:
        template<class Type>
        [[maybe_unused]] void set(const std::string &name, const Type &value) {
            if (genes_id.find(name) == genes_id.end())
                throw std::out_of_range("Name not found");
            set(genes_id[name], value);
        }

        template<class Type>
        [[maybe_unused]] void set(size_t id, const Type &value) {
            if (genes.size() <= id)
                throw std::out_of_range("Id not found");
            if (genes[id].has_value())
                throw std::out_of_range("the gene value is already recorded.");
            genes[id].emplace<Type>(value);
        }
    };
} // hgem

#endif //GENOME_GENOME_H
