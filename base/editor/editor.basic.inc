<?php

	namespace Base\Editor;

	abstract class Basic {
		protected string $name;

		protected function __construct(string $name) {
			$this->name = $name;
		}

	}