// SPDX-FileCopyrightText: 2015-2024 Alexey Rochev
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef TREMOTESF_LABELSMODEL_H
#define TREMOTESF_LABELSMODEL_H

#include <vector>

#include "basetorrentsfilterssettingsmodel.h"

namespace tremotesf {
    class LabelsModel final : public BaseTorrentsFiltersSettingsModel {
        Q_OBJECT

    public:
        static constexpr auto LabelRole = Qt::UserRole;

        inline explicit LabelsModel(QObject* parent = nullptr) : BaseTorrentsFiltersSettingsModel(parent) {};

        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        int rowCount(const QModelIndex& = {}) const override;

        QModelIndex indexForTorrentsProxyModelFilter() const override;

        struct LabelItem {
            QString label;
            int torrents;
        };

    protected:
        void resetTorrentsProxyModelFilter() const override;

    private:
        void update() override;

        std::vector<LabelItem> mLabels;
    };
}

#endif // TREMOTESF_LABELSMODEL_H
