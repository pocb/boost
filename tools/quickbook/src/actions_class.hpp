/*=============================================================================
    Copyright (c) 2002 2004 2006 Joel de Guzman
    Copyright (c) 2004 Eric Niebler
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_ACTIONS_CLASS_HPP)
#define BOOST_SPIRIT_ACTIONS_CLASS_HPP

#include "actions.hpp"
#include "parsers.hpp"
#include "values_parse.hpp"
#include <boost/tuple/tuple.hpp>
#include <boost/scoped_ptr.hpp>

namespace quickbook
{
    namespace cl = boost::spirit::classic;
    namespace fs = boost::filesystem;

    struct actions
    {
        actions(fs::path const& filein_, fs::path const& outdir, string_stream& out_);

    private:
        boost::scoped_ptr<quickbook_grammar> grammar_;

    public:
    ///////////////////////////////////////////////////////////////////////////
    // State
    ///////////////////////////////////////////////////////////////////////////

        typedef std::vector<std::string> string_list;

        typedef std::pair<char, int> mark_type;
        static int const max_template_depth = 100;

    // header info
        std::string             doc_type;
        std::string             doc_title_qbk;
        std::string             doc_id;

    // main output stream
        collector               out;

    // auxilliary streams
        collector               phrase;
        collector               list_buffer;

    // value actions
        value_parser            values;
        collector_to_value_action phrase_value;
        collector_to_value_action out_value;
        phrase_to_docinfo_action docinfo_value;
        
        scoped_parser<cond_phrase_push>
                                scoped_cond_phrase;
        scoped_parser<scoped_output_push>
                                scoped_output;
        scoped_parser<set_no_eols_scoped>
                                scoped_no_eols;

    // state
        fs::path                filename;
        fs::path                outdir;
        std::size_t             macro_change_depth;
        string_symbols          macro;
        int                     section_level;
        int                     min_section_level;
        std::string             section_id;
        std::string             qualified_section_id;
        std::string             source_mode;

        typedef boost::tuple<
            fs::path
          , fs::path
          , std::size_t
          , int
          , int
          , std::string
          , std::string
          , std::string>
        state_tuple;

        std::stack<state_tuple> state_stack;
        // Stack macros separately as copying macros is expensive.
        std::stack<string_symbols> macro_stack;

    // temporary or global state
        std::string             macro_id;
        std::stack<mark_type>   list_marks;
        int                     list_indent;
        int                     template_depth;
        template_stack          templates;
        int                     error_count;
        string_list             anchors;
        bool                    no_eols;
        bool                    suppress;
        bool                    warned_about_breaks;

    // push/pop the states and the streams
        void copy_macros_for_write();
        void push();
        void pop();
        quickbook_grammar& grammar() const;

    ///////////////////////////////////////////////////////////////////////////
    // actions
    ///////////////////////////////////////////////////////////////////////////

        element_action          element;
        error_action            error;

        code_action             code;
        code_action             code_block;
        inline_code_action      inline_code;
        implicit_paragraph_action inside_paragraph;
        markup_action           hr;
        space                   space_char;
        plain_char_action       plain_char;
        raw_char_action         raw_char;
        escape_unicode_action   escape_unicode;
        image_action            image;

        list_action             list;
        list_format_action      list_format;
        phrase_action           list_item;

        link_action             funcref_pre;
        markup_action           funcref_post;
        link_action             classref_pre;
        markup_action           classref_post;
        link_action             memberref_pre;
        markup_action           memberref_post;
        link_action             enumref_pre;
        markup_action           enumref_post;
        link_action             macroref_pre;
        markup_action           macroref_post;
        link_action             headerref_pre;
        markup_action           headerref_post;
        link_action             conceptref_pre;
        markup_action           conceptref_post;
        link_action             globalref_pre;
        markup_action           globalref_post;

        tagged_action           bold;
        tagged_action           italic;
        tagged_action           underline;
        tagged_action           teletype;
        tagged_action           strikethrough;
        tagged_action           quote;
        tagged_action           replaceable;
        tagged_action           footnote;

        simple_phrase_action    simple_bold;
        simple_phrase_action    simple_italic;
        simple_phrase_action    simple_underline;
        simple_phrase_action    simple_teletype;
        simple_phrase_action    simple_strikethrough;

        break_action            break_;
        do_macro_action         do_macro;
        do_template_action      do_template;
        link_action             url_pre;
        markup_action           url_post;
        link_action             link_pre;
        markup_action           link_post;
        anchor_action           anchor;

        element_id_warning_action element_id_warning;

        markup_action           escape_pre;
        markup_action           escape_post;

        pre_output_action       output_pre;
    };
}

#endif // BOOST_SPIRIT_ACTIONS_CLASS_HPP

