<?php

	namespace Base\Templates;

	abstract class Layout {
		private static array $stylesheets = [];

		public function __construct() {  }

		public static function AddStylesheet($name, $url) {
			if (isset(self::$stylesheets[$name])) die("Stylesheet «{$name}» exists");
			self::$stylesheets[$name] = $url;
		}

		public static function BrowseStylesheets() {
			foreach (self::$stylesheets as $stylesheet) { ?><link rel = "stylesheet" href = "<?= $stylesheet; ?>" type = "text/css"><?php }
		}

	}