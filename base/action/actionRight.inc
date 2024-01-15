<?php

	namespace Base;

	class ActionRight extends Action {
		public int $collection;

		public function __construct(int $collection, string $area = 'null', string $part = 'null', string $href = '', string $click = '') {
			parent::__construct($area, $part, $href, $click);

			$this->collection = $collection;
		}

		/**
		 * Возвращает ссылку для href
		 * @param int $right - Право
		 * @param string $content - Контент
		 * @param array $data - Данные для замены
		 * @param array $params - Параметры
		 * @return string
		 */
		public function GetLinkHrefAllow(int $right, string $content, array $data = [], array $params = []): string {
			if (!Access::Allow($right, $this->collection)) return '';

			return $this->GetLinkHref($content, $data, $params);
		}

	}