<?php

	namespace Base\Templates;

	abstract class Layout {
		private static array $stylesheets = [];
		private static array $scripts = [];

		private static string $title = '';
		private static string $description = '';
		private static array $data = [];

		public function __construct() {  }

		public static function AddScript(string $name, string $src) : void {
			if (isset(self::$scripts[$name])) die("Script «{$name}» exists");
			self::$scripts[$name] = $src;
		}

		public static function AddStylesheet(string $name, string $url): void {
			if (isset(self::$stylesheets[$name])) die("Stylesheet «{$name}» exists");
			self::$stylesheets[$name] = $url;
		}

		public static function AddVersionScript(string $name, string $file_path_and_name, string $version) : void {
			if (isset(self::$scripts[$name])) die("Script «{$name}» exists");
			self::$scripts[$name] = "{$file_path_and_name}.{$version}.js";
		}

		public static function AddVersionStylesheet(string $name, string $file_path_and_name, string $version): void {
			if (isset(self::$stylesheets[$name])) die("Stylesheet «{$name}» exists");
			self::$stylesheets[$name] ="{$file_path_and_name}.{$version}.css";
		}

		public static function SetData(string $name, string $value): void { self::$data[$name] = $value; }
		public static function SetDataPage(string $value): void { self::SetData('page', $value); }

		public static function SetTitle(string $title): void { self::$title = $title; }
		public static function SetDescription(string $description): void { self::$description = $description; }

		public static function BrowseStylesheets(): void {
			foreach (self::$stylesheets as $url) { ?><link rel = "stylesheet" href = "<?= $url; ?>" type = "text/css"><?php }
		}

		public static function BrowseScripts(): void {
			foreach (self::$scripts as $src) { ?><script src = "<?= $src; ?>"></script><?php }
		}

		public static function BrowseData(): void {
			if (!static::$data) return;

			$list = '';
			foreach (self::$data as $name => $value) $list .= " data-{$name} = \"{$value}\"";

			echo $list;
		}

		public static function BrowseHead(): void {
			self::BrowseScripts();
			self::BrowseStylesheets();
			if (self::$title) ?><title><?= self::$title; ?></title><?php
			if (self::$description) ?><meta name = "description" content = "<?= self::$description; ?>"><?php
		}

	}