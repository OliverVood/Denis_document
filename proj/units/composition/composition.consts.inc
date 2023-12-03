<?php

	namespace Proj\Units\Consts;

	interface Composition {
		const ID						= ID_COMPOSITION;
		const NAME						= 'composition';

		const FILE_CONTROLLER			= 1;
		const FILE_STRUCTURE			= 2;
		const FILE_ACTIONS				= 4;
		const FILE_MODEL				= 8;

		const ROUTES = [
			1							=> 'admin',
			2							=> 'site'
		];

		const ENTRIES = [
			1							=> 'html',
			2							=> 'xhr'
		];

	}