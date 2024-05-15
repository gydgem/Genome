//
// Created by gydgem on 09.05.24.
//

#ifndef GENOME_GENE_H
#define GENOME_GENE_H

#include "genome_common.h"

namespace hgem {
    template<class Type>
    class gene {
    protected:
        std::mt19937_64 rand_gene;

    protected:
        std::vector<Type> gene_staff;
        std::pair<Type, Type> range_of_values;

    public:
        gene() = default;

        gene(const std::pair<Type, Type> &new_range_of_values)
                : range_of_values(new_range_of_values), gene_staff(1) {
            mutation();
        }

        gene(const std::pair<Type, Type> &new_range_of_values, size_t size)
                : range_of_values(new_range_of_values), gene_staff(size) {
            mutation(100);
        }

        gene(const std::pair<Type, Type> &new_range_of_values,
             const std::vector<Type> &new_value)
                : range_of_values(new_range_of_values), gene_staff(new_value) {
        }

        virtual ~gene() = default;

    private:
        template<class Type_value>
        [[noreturn]] static void MakeLine(std::vector<Type> &res, const Type_value &value) {
            throw std::invalid_argument("data types are distinguished");
        }

        static void MakeLine(std::vector<Type> &res, const Type &value) {
            res.emplace_back(value);
        }

        static void MakeLine(std::vector<Type> &res, const std::vector<Type> &value) {
            res.insert(res.end(), value.begin(), value.end());
        }

        template<class Type_value>
        static void MakeLine(std::vector<Type> &res, const std::vector<Type_value> &value) {
            for (size_t index = 0; index < value.size(); index++)
                MakeLine(res, value[index]);
        }

        template<class Type_value_first, class Type_value_second>
        static void MakeLine(std::vector<Type> &res, const std::pair<Type_value_first, Type_value_second> &value) {
            MakeLine(value.first, res);
            MakeLine(value.second, res);
        }

        template<class Type_value, class... Types_value>
        static void MakeLine(std::vector<Type> &res, const Type_value &value, Types_value... remaining_values) {
            MakeLine(res, value);
            MakeLine(res, remaining_values...);
        }

    public:
        static std::vector<Type> MakeLine() {
            return {};
        }

        static std::vector<Type> MakeLine(const Type &value) {
            return {value};
        }

        static std::vector<Type> MakeLine(const std::vector<Type> &value) {
            return value;
        }

        template<class Type_value>
        static std::vector<Type> MakeLine(const std::vector<Type_value> &value) {
            std::vector<Type> res;
            MakeLine(res, value);
            return res;
        }

        template<class Type_value_first, class Type_value_second>
        static std::vector<Type> MakeLine(const std::pair<Type_value_first, Type_value_second> &value) {
            std::vector<Type> res;
            MakeLine(res, value);
            return res;
        }

        template<class Type_value, class... Types_value>
        static std::vector<Type> MakeLine(const Type_value &value, Types_value... remaining_values) {
            std::vector<Type> res;
            MakeLine(res, value, remaining_values...);
            return res;
        }

    public:
        [[nodiscard]] size_t size() const {
            return gene_staff.size();
        }

    public:
        [[nodiscard]] const std::vector<Type> &at() const {
            return gene_staff;
        }

        [[nodiscard]] const Type &at(size_t index) const {
            return gene_staff[index];
        }

    public:
        [[nodiscard]] const Type &operator[](size_t index)const {
            return gene_staff[index];
        }

    public:
        [[nodiscard]] virtual Type gene_interaction_value(const std::vector<Type> &value) const {
            if (value.size() != gene_staff.size())
                throw std::out_of_range("Vectors must be of the same size.");
            Type res = 0;
            for (size_t index = 0; index < value.size(); index++)
                res += gene_staff[index] * value[index];
            return res;
        }

        [[nodiscard]] Type gene_interaction_value(const gene<Type> &value) const {
            gene_interaction_value(value.gene_staff);
        }
        
        template<class Type_value>
        [[nodiscard]] Type gene_interaction_value(const Type_value &value) const {
            std::vector<Type> temporary = MakeLine(value);
            gene_interaction_value(temporary);
        }

        template<class... Type_values>
        [[nodiscard]] Type gene_interaction_value(Type_values... values) const {
            std::vector<Type> temporary = MakeLine(values...);
            gene_interaction_value(temporary);
        }

    public:
        virtual void mutation() {
            mutation(10);
        }

        virtual void mutation(size_t chance_mutation) {
            if (chance_mutation > 100 || chance_mutation < 0)
                throw std::out_of_range("chance mutation dont correct ");
            for (size_t index = 0; index < gene_staff.size(); index++) {
                if (rand_gene() % 101 < chance_mutation)
                    gene_staff[index] =
                            rand_gene() % (range_of_values.second - range_of_values.first + 1) + range_of_values.first;
            }
        }
    };
} // hgem

#endif //GENOME_GENE_H
