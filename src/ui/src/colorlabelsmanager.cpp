/*
 * Copyright (C) 2021 Anton Filimonov and other contributors
 *
 * This file is part of klogg.
 *
 * klogg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * klogg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with klogg.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "colorlabelsmanager.h"

ColorLabelsManager::QuickHighlightersCollection ColorLabelsManager::colorLabels() const
{
    return quickHighlighters_;
}

ColorLabelsManager::QuickHighlightersCollection ColorLabelsManager::clear()
{
    for ( auto& quickHighlighters : quickHighlighters_ ) {
        quickHighlighters.clear();
    }
    return quickHighlighters_;
}

ColorLabelsManager::QuickHighlightersCollection
ColorLabelsManager::setColorLabel( size_t label, const QString& text )
{
    return updateColorLabel( label, text, true );
}

ColorLabelsManager::QuickHighlightersCollection
ColorLabelsManager::setNextColorLabel( const QString& text )
{
    const auto nextLabel = nextQuickHighlighterIndex_;
    nextQuickHighlighterIndex_++;
    if ( nextQuickHighlighterIndex_ == quickHighlighters_.size() ) {
        nextQuickHighlighterIndex_ = 0;
    }

    return updateColorLabel( nextLabel, text, false );
}

ColorLabelsManager::QuickHighlightersCollection
ColorLabelsManager::updateColorLabel( size_t label, const QString& text, bool replaceCurrent )
{
    auto wasHighlightedAnyLabel = false;
    auto wasHighlightedOtherLabel = false;

    for ( auto i = 0u; i < quickHighlighters_.size(); ++i ) {
        const auto wasHighlighted = quickHighlighters_[ i ].removeAll( text ) != 0;
        wasHighlightedAnyLabel |= wasHighlighted;
        wasHighlightedOtherLabel |= ( wasHighlighted && i != label );
    }

    if ( !( wasHighlightedAnyLabel ) || ( wasHighlightedOtherLabel && replaceCurrent ) ) {
        quickHighlighters_[ label ].append( std::move( text ) );
    }

    return quickHighlighters_;
}