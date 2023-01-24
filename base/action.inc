<?php

	namespace Base;

	Class Action {
		public string $area;
		public string $part;

		public string $path;
		private string $href;
		private string $click;

		public function __construct(string $area = 'null', string $part = 'null', string $href = '', string $click = '') {
			$this->area 	= $area;
			$this->part 	= $part;

			$this->href 	= $href;
			$this->click 	= $click;

			$this->path		= '';
			if ($this->area !== 'null') $this->path .= "/{$this->area}";
			if ($this->part !== 'null') $this->path .= "/{$this->part}";

			if ($href == 'default') $this->href = REQUEST . $this->path;
		}

		/**
		 * Возвращает ссылку
		 * @param string $content - Контент
		 * @param array $data - Параметры
		 * @param array $params - Параметры
		 * @return string
		 */
		public function GetLink(string $content, array $data = [], array $params = []): string {
			$href = ' href = "' . $this->path . '"';
			$onclick = ' onclick = "' . $this->click . '"';
			$target = (isset($params['target'])) ? ' target = "' . $params['target'] . '"' : '';

			return "<a{$href}{$onclick}{$target}>{$content}</a>";
		}

		/**
		 * Возвращает href
		 * @return string
		 */
		public function GetPath(): string {
			return $this->path;
		}

		/**
		 * Возвращает href
		 * @return string
		 */
		public function GetHref(): string {
			return $this->href;
		}

		private function ParseTarget(string $subject, array $replace): string {//TODO
//			foreach ($replace) ;
			return  $subject;
		}

	}