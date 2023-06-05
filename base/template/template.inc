<?php

	namespace Base\Templates;

	abstract class Template extends Buffering {
		private array $stylesheets = [];
		private array $scripts = [];

		private string $title = '';
		private string $description = '';
		private string $keywords = '';

		private array $data = [];

		protected function __construct() {  }

		public function AddScript(string $name, string $src) : void {
			if (isset($this->scripts[$name])) die("Script «{$name}» exists");
			$this->scripts[$name] = $src;
		}

		public function AddStylesheet(string $name, string $url): void {
			if (isset($this->stylesheets[$name])) die("Stylesheet «{$name}» exists");
			$this->stylesheets[$name] = $url;
		}

		public function AddVersionScript(string $name, string $file_path_and_name, string $version) : void {
			if (isset($this->scripts[$name])) die("Script «{$name}» exists");
			$this->scripts[$name] = "{$file_path_and_name}.{$version}.js";
		}

		public function AddVersionStylesheet(string $name, string $file_path_and_name, string $version): void {
			if (isset($this->stylesheets[$name])) die("Stylesheet «{$name}» exists");
			$this->stylesheets[$name] ="{$file_path_and_name}.{$version}.css";
		}

		public function SetTitle(string $title): void { $this->title = $title; }
		public function SetDescription(string $description): void { $this->description = $description; }
		public function SetKeywords(string $keywords): void { $this->keywords = $keywords; }

		public function SetData(string $name, string $value): void { $this->data[$name] = $value; }
		public function SetDataPage(string $value): void { $this->SetData('page', $value); }

		public function BrowseStylesheets(): void {
			foreach ($this->stylesheets as $url) { ?><link rel = "stylesheet" href = "<?= $url; ?>" type = "text/css"><?php }
		}

		private function BrowseScripts(): void {
			foreach ($this->scripts as $src) { ?><script src = "<?= $src; ?>"></script><?php }
		}

		protected function BrowseHead(): void {
			$this->BrowseScripts();
			$this->BrowseStylesheets();
			if ($this->title) ?><title><?= $this->title; ?></title><?php
			if ($this->description) ?><meta name = "description" content = "<?= $this->description; ?>"><?php
			if ($this->keywords) ?><meta name = "keywords" content = "<?= $this->keywords; ?>"><?php
		}

		public function BrowseData(): void {
			if (!$this->data) return;

			$list = '';
			foreach ($this->data as $name => $value) $list .= " data-{$name} = \"{$value}\"";

			echo $list;
		}

	}