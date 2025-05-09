/*
 * TODO: parse a --wasm argument to get the location of wasm bin files
 * TODO: edit flake.nix to add --wasm ${... "wasm"} to pass in wasm bin files automatically
 * TODO: do a directory search for src files in flake.nix
 * TODO: test if wasm works in js
 * TODO: test a wasm memory interface
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "conf.h"
#include "meta.h"
#include "mustach/mustach.h"
#include "tmpl.h"

#include <unistd.h>

int main(int argc, char **argv) {

  printf("PARSING METADATA FILE " METADATA_FILE "\n");
  meta_t *meta = meta_parse(METADATA_FILE);
  meta_debug(meta);

  printf("SETTING UP OUTPUT DIRECTORY " OUTPUT_DIR "\n");
  make_output_dir(OUTPUT_DIR);
  make_output_dir(OUTPUT_DIR "/post");
  make_output_dir(OUTPUT_DIR "/scripts");
  make_output_dir(OUTPUT_DIR "/scripts/post");
  make_output_dir(OUTPUT_DIR "/tag");
  make_output_dir(OUTPUT_DIR "/wasm");

  copy_files(STATIC_DIR, OUTPUT_DIR);
  copy_files(STATIC_DIR "/scripts", OUTPUT_DIR "/scripts");
  copy_files(STATIC_DIR "/scripts/post", OUTPUT_DIR "/scripts/post");

  printf("GENERATING PAGES\n");

  closure_t closure = {
      .meta = meta,
      .state = ROOT,
      .index = 0,
      .index_inner = 0,
  };

  for (uint32_t i = 0; i < meta->num_pages; ++i) {
    printf("  " OUTPUT_DIR "/%s\n", meta->pages[i]);
    string_t tmpl = read_template(meta->pages[i]);
    render_file(&closure, tmpl, meta->pages[i], "html");
    free(tmpl.data);
  }
  printf("  " OUTPUT_DIR "/rss.xml\n");
  string_t tmpl = read_template("rss");
  render_file(&closure, tmpl, "rss", "xml");
  free(tmpl.data);

  string_t tmpl_post = read_template("post");
  closure.state = POST;
  for (size_t i = 0; i < meta->num_posts; ++i) {
    closure.index = i;
    char slug[256];
    snprintf(slug, sizeof(slug), "post/%s", meta->posts[i].slug);
    printf("  " OUTPUT_DIR "/%s\n", slug);
    render_file(&closure, tmpl_post, slug, "html");
  }
  free(tmpl_post.data);

  string_t tmpl_tag = read_template("tag");
  closure.state = TAG;
  for (size_t i = 0; i < meta->num_tags; ++i) {
    closure.index = i;
    char slug[256];
    snprintf(slug, sizeof(slug), "tag/%s", meta->tags[i].id);
    printf("  " OUTPUT_DIR "/%s\n", slug);
    render_file(&closure, tmpl_tag, slug, "html");
  }
  free(tmpl_tag.data);

  meta_free(meta);
}
